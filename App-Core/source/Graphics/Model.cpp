#include "Graphics/Model.h"
#include "Graphics/Mesh.h"
#include "Core/Log.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Graphics
{
    const u32 ModelLoadFlags =
        aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices;

    static Mesh ProcessMesh(aiMesh* aMesh, const aiScene* aScene, Model& model)
    {
        Mesh mesh;

        std::vector<Vertex> vertices;
        std::vector<u32> indices;

        for (u32 i = 0; i < aMesh->mNumVertices; i++)
        {
            Vertex vertex;

            vertex.position.x = aMesh->mVertices[i].x;
            vertex.position.y = aMesh->mVertices[i].y;
            vertex.position.z = aMesh->mVertices[i].z;

            if (aMesh->HasNormals())
            {
                vertex.normal.x = aMesh->mNormals[i].x;
                vertex.normal.y = aMesh->mNormals[i].y;
                vertex.normal.z = aMesh->mNormals[i].z;
            }

            if (aMesh->HasTextureCoords(0))
            {
                vertex.uvCoords.x = aMesh->mTextureCoords[0][i].x;
                vertex.uvCoords.y = aMesh->mTextureCoords[0][i].y;
            }
            else
                vertex.uvCoords = glm::vec2(0.f);

            vertices.push_back(vertex);
        }

        for (u32 i = 0; i < aMesh->mNumFaces; i++)
        {
            aiFace face = aMesh->mFaces[i];

            for (u32 j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }

        aiMaterial* aMaterial = aScene->mMaterials[aMesh->mMaterialIndex];
        Material& material = model.materials[aMesh->mMaterialIndex];

        aiString aPath;
        aMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &aPath);

        bool skip = false;
        for (u32 i = 0; i < model.loadedTextures.size(); i++)
        {
            if (std::strcmp(model.loadedTextures[i].path.c_str(), aPath.C_Str()) == 0)
            {
                skip = true;
                material.diffuseMap = model.loadedTextures[i];
                break;
            }
        }

        if (!skip)
        {
            Texture texture = LoadTexture(aPath.C_Str(), TEX_FMT_RGBA);
            material.diffuseMap = texture;
            model.loadedTextures.push_back(texture);
        }

        aiColor3D diffuseColor(0.f, 0.f, 0.f);
        aiColor3D specularColor(0.f, 0.f, 0.f);

        if (aMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, diffuseColor) == AI_SUCCESS)
            material.diffuse = glm::vec3(diffuseColor.r, diffuseColor.g, diffuseColor.b);

        if (aMaterial->Get(AI_MATKEY_COLOR_SPECULAR, specularColor) == AI_SUCCESS)
            material.specular = glm::vec3(specularColor.r, specularColor.g, specularColor.b);

        mesh = LoadMesh(vertices.data(), vertices.size(), indices.data(), indices.size(),
                        aMesh->mMaterialIndex);

        return mesh;
    }

    static void ProcessNode(aiNode* aNode, const aiScene* aScene, Model& model)
    {
        for (u32 i = 0; i < aNode->mNumMeshes; i++)
        {
            aiMesh* aMesh = aScene->mMeshes[aNode->mMeshes[i]];
            Mesh mesh = ProcessMesh(aMesh, aScene, model);
            model.meshes.push_back(mesh);
        }

        for (u32 i = 0; i < aNode->mNumChildren; i++)
            ProcessNode(aNode->mChildren[i], aScene, model);
    }

    Model LoadModel(const char* path)
    {
        Model model;
        model.path = path;

        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path, ModelLoadFlags);

        if (scene == NULL || scene->mRootNode == NULL)
        {
            WARN("Failed to load model %s!", path);
            return model;
        }

        model.materials.resize(scene->mNumMaterials);
        ProcessNode(scene->mRootNode, scene, model);

        INFO("Successfully loaded model %s!", path);
        return model;
    }

    void LogModelInfo(Model& model)
    {
        INFO("=======Model info=======");
        INFO("Model path                 : %s", model.path.c_str());
        INFO("Model mesh count           : %d", model.meshes.size());
        INFO("Model material count       : %d", model.materials.size());
        INFO("Model loaded texture count : %d", model.loadedTextures.size());
    }

    void UnloadModel(Model& model)
    {
        INFO("Unloading model %s...", model.path.c_str());

        for (u32 i = 0; i < model.meshes.size(); i++)
            UnloadMesh(model.meshes[i]);

        for (u32 i = 0; i < model.materials.size(); i++)
            UnloadTexture(model.materials[i].diffuseMap);

        model.meshes = std::vector<Mesh>();
    }

}
