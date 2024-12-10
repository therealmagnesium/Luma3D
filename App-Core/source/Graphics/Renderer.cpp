#include "Graphics/Renderer.h"
#include "Graphics/Shader.h"
#include "Graphics/Texture.h"
#include "Graphics/Window.h"

#include "Core/Application.h"
#include "Core/Log.h"
#include "Core/Time.h"

#include "UI/UI.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

namespace Graphics
{
    RenderState Renderer;

    static bool isInitialized = false;

    static void SetupUniforms()
    {
        Renderer.defaultShader.uniformLocs[SHADER_LOC_COLOR_DIFFUSE] =
            GetUniformLocation(Renderer.defaultShader, "material.diffuse");

        Renderer.defaultShader.uniformLocs[SHADER_LOC_COLOR_SPECULAR] =
            GetUniformLocation(Renderer.defaultShader, "material.specular");

        Renderer.defaultShader.uniformLocs[SHADER_LOC_VALUE_ROUGHNESS] =
            GetUniformLocation(Renderer.defaultShader, "material.roughness");

        Renderer.defaultShader.uniformLocs[SHADER_LOC_VALUE_METALIC] =
            GetUniformLocation(Renderer.defaultShader, "material.metalic");

        Renderer.defaultShader.uniformLocs[SHADER_LOC_MAP_DIFFUSE] =
            GetUniformLocation(Renderer.defaultShader, "material.diffuseMap");

        Renderer.defaultShader.uniformLocs[SHADER_LOC_VECTOR_VIEW] =
            GetUniformLocation(Renderer.defaultShader, "cameraPosition");

        Renderer.defaultShader.uniformLocs[SHADER_LOC_MATRIX_MODEL] =
            GetUniformLocation(Renderer.defaultShader, "matModel");

        Renderer.defaultShader.uniformLocs[SHADER_LOC_MATRIX_VIEW] =
            GetUniformLocation(Renderer.defaultShader, "matView");

        Renderer.defaultShader.uniformLocs[SHADER_LOC_MATRIX_PROJECTION] =
            GetUniformLocation(Renderer.defaultShader, "matProjection");

        Renderer.defaultShader.uniformLocs[SHADER_LOC_MATRIX_NORMAL] =
            GetUniformLocation(Renderer.defaultShader, "matNormal");

        Renderer.defaultShader.Bind();

        Renderer.defaultShader.SetInt(Renderer.defaultShader.uniformLocs[SHADER_LOC_MAP_DIFFUSE],
                                      SHADER_LOC_MAP_DIFFUSE);

        Renderer.defaultShader.Unbind();
    }

    void RendererInit()
    {
        if (isInitialized)
        {
            ERROR("Cannot initialize renderer more than once!");
            return;
        }

        Renderer.clearColor = glm::vec4(0.08f, 0.1f, 0.12f, 1.f);

        const char* vertPath = "assets/shaders/Default_vs.glsl";
        const char* fragPath = "assets/shaders/Default_fs.glsl";
        Renderer.defaultShader = LoadShader(vertPath, fragPath);

        SetupUniforms();

        TextureFormatsInit();
        glEnable(GL_DEPTH_TEST);

        isInitialized = true;
        INFO("Successfully initialized the renderer!");
    }

    void RendererShutdown()
    {
        if (!isInitialized)
        {
            ERROR("Cannot shutdown renderer because it's not initialized!");
            return;
        }

        INFO("Shutting down the renderer...");
        UnloadShader(Renderer.defaultShader);

        isInitialized = false;
    }

    void RendererBegin()
    {
        Renderer.ClearContext(Renderer.clearColor);
    }

    void RendererEnd()
    {
        Window& window = Core::App->GetWindow();

        UI::RenderFrame();
        SDL_GL_SwapWindow(window.handle);
        Core::UpdateTimeLate();
    }

    void SetPrimaryCamera(Camera* camera)
    {
        Renderer.primaryCamera = camera;
    }

    void RenderState::ClearContext(const glm::vec4& color)
    {
        clearColor = color;
        glClearColor(V4_OPEN(clearColor));
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Window& window = Core::App->GetWindow();
        float aspectRatio = (float)window.width / (float)window.height;
        projection = glm::perspective(glm::radians(45.f), aspectRatio, 0.1f, 1000.f);
    }

    void RenderState::DrawMesh(Mesh& mesh, Shader& shader, Material& material)
    {
        shader.Bind();

        material.diffuseMap.Bind(0);

        shader.SetVec3(shader.uniformLocs[SHADER_LOC_COLOR_DIFFUSE],
                       glm::value_ptr(material.diffuse));

        shader.SetVec3(shader.uniformLocs[SHADER_LOC_COLOR_SPECULAR],
                       glm::value_ptr(material.specular));

        shader.SetFloat(shader.uniformLocs[SHADER_LOC_VALUE_ROUGHNESS], material.roughness);
        shader.SetFloat(shader.uniformLocs[SHADER_LOC_VALUE_METALIC], material.metalic);

        shader.SetInt(shader.uniformLocs[SHADER_LOC_MAP_DIFFUSE], 0);

        shader.SetMat4(shader.uniformLocs[SHADER_LOC_MATRIX_VIEW],
                       glm::value_ptr(primaryCamera->view));

        shader.SetMat4(shader.uniformLocs[SHADER_LOC_MATRIX_PROJECTION],
                       glm::value_ptr(projection));

        mesh.vertexArray.Bind();
        mesh.indexBuffer.Bind();

        glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, NULL);

        mesh.indexBuffer.Unbind();
        mesh.vertexArray.Unbind();

        material.diffuseMap.Unbind();

        shader.Unbind();
    }

    void RenderState::DrawModel(Model& model, Shader& shader, glm::vec3 position,
                                glm::vec3 rotation, glm::vec3 scale)
    {
        model.transform = glm::mat4(1.f);
        model.transform = glm::translate(model.transform, position);
        model.transform =
            glm::rotate(model.transform, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
        model.transform =
            glm::rotate(model.transform, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
        model.transform =
            glm::rotate(model.transform, glm::radians(rotation.z), glm::vec3(1.f, 0.f, 1.f));
        model.transform = glm::scale(model.transform, scale);

        glm::mat4 normal = glm::mat4(1.f);
        normal = glm::transpose(glm::inverse(model.transform));

        shader.Bind();

        shader.SetVec3(shader.uniformLocs[SHADER_LOC_VECTOR_VIEW],
                       glm::value_ptr(primaryCamera->position));
        shader.SetMat4(shader.uniformLocs[SHADER_LOC_MATRIX_MODEL],
                       glm::value_ptr(model.transform));
        shader.SetMat4(shader.uniformLocs[SHADER_LOC_MATRIX_NORMAL], glm::value_ptr(normal));

        shader.Unbind();

        for (u32 i = 0; i < model.meshes.size(); i++)
            this->DrawMesh(model.meshes[i], shader, model.materials[model.meshes[i].materialIndex]);
    }

    void RenderState::DrawSkybox(Skybox& skybox, Shader& shader)
    {
        glDepthFunc(GL_LEQUAL);
        shader.Bind();
        skybox.Bind(0);

        shader.SetInt(shader.uniformLocs[SHADER_LOC_MAP_DIFFUSE], 0);

        shader.SetMat4(shader.uniformLocs[SHADER_LOC_MATRIX_VIEW],
                       (float*)glm::value_ptr(glm::mat4(glm::mat3(primaryCamera->view))));

        shader.SetMat4(shader.uniformLocs[SHADER_LOC_MATRIX_PROJECTION],
                       glm::value_ptr(projection));

        skybox.cube.meshes[0].vertexArray.Bind();
        skybox.cube.meshes[0].indexBuffer.Bind();

        glDrawElements(GL_TRIANGLES, skybox.cube.meshes[0].indices.size(), GL_UNSIGNED_INT, NULL);

        skybox.cube.meshes[0].indexBuffer.Unbind();
        skybox.cube.meshes[0].vertexArray.Unbind();
        shader.Unbind();
        glDepthFunc(GL_LESS);
    }
}
