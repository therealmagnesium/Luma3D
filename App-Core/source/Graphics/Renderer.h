#pragma once
#include "Core/Base.h"

#include "Graphics/Camera.h"
#include "Graphics/Mesh.h"
#include "Graphics/Model.h"
#include "Graphics/Shader.h"
#include "Graphics/Skybox.h"

#include <glm/glm.hpp>

namespace Graphics
{
    struct RenderState
    {
        Shader defaultShader;
        glm::vec4 clearColor = glm::vec4(1.f);
        glm::mat4 projection = glm::mat4(1.f);
        Camera* primaryCamera = NULL;

        void ClearContext(const glm::vec4& color);
        void DrawMesh(Mesh& mesh, Shader& shader, Material& material);
        void DrawModel(Model& model, Shader& shader, glm::vec3 position, glm::vec3 rotation,
                       glm::vec3 scale);
        void DrawSkybox(Skybox& skybox, Shader& shader);
    };

    extern RenderState Renderer;

    void RendererInit();
    void RendererShutdown();
    void RendererBegin();
    void RendererEnd();
    void SetPrimaryCamera(Camera* camera);
}
