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

        void ClearContext(u32 bufferLevel = 0);
        void DrawMesh(Mesh& mesh, Shader& shader, glm::mat4& transform, Material& material);
        void DrawModel(Model& model, Shader& shader);
        void DrawSkybox(Skybox& skybox, Shader& shader);
    };

    extern RenderState Renderer;

    void RendererInit();
    void RendererShutdown();
    void RendererBegin();
    void RendererEnd();
    void SetPrimaryCamera(Camera* camera);
}
