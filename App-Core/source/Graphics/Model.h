#pragma once
#include "Graphics/Mesh.h"
#include "Graphics/Material.h"
#include "Graphics/Texture.h"
#include "Core/Base.h"

#include <vector>
#include <glm/glm.hpp>

namespace Graphics
{
    struct Model
    {
        glm::mat4 transform = glm::mat4(1.f);
        std::string path;
        std::vector<Mesh> meshes;
        std::vector<Material> materials;
        std::vector<Texture> loadedTextures;
    };

    Model LoadModel(const char* path);
    void LogModelInfo(Model& model);
    void UnloadModel(Model& model);
}
