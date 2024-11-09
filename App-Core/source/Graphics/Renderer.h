#pragma once
#include "Core/Base.h"
#include "Graphics/Mesh.h"
#include "Graphics/Shader.h"
#include <glm/glm.hpp>

namespace Graphics
{
    struct RenderState
    {
        Shader defaultShader;
        glm::vec4 clearColor;
        glm::mat4 projection;

        void ClearContext(const glm::vec4& color);
        void DrawMesh(Mesh& mesh, Shader& shader);
    };

    extern RenderState Renderer;

    void RendererInit();
    void RendererShutdown();
}
