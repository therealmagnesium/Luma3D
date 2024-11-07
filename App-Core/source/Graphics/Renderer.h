#pragma once
#include "Core/Base.h"
#include "Graphics/Mesh.h"
#include "Graphics/Shader.h"
#include <glm/glm.hpp>

namespace Graphics
{
    class RenderState
    {
    public:
        RenderState() = default;

        static void Init();
        void ClearContext(const glm::vec4& color);
        void DrawMesh(Mesh& mesh, Shader& shader);

        inline Shader& GetDefaultShader() { return m_defaultShader; }
        inline glm::mat4& GetProjection() { return m_projection; }

    private:
        Shader m_defaultShader;
        glm::vec4 m_clearColor;
        glm::mat4 m_projection;
    };

    extern RenderState Renderer;
}
