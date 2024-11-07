#include "Graphics/Renderer.h"
#include "Core/Log.h"
#include "Graphics/Shader.h"

#include <glm/glm.hpp>
#include <glad/glad.h>

namespace Graphics
{
    RenderState Renderer;
    bool isInitialized = false;

    void RenderState::Init()
    {
        if (isInitialized)
        {
            ERROR("Cannot initialize renderer more than once!");
            return;
        }

        const char* vertPath = "assets/shaders/Default_vs.glsl";
        const char* fragPath = "assets/shaders/Default_fs.glsl";
        Renderer.m_defaultShader = LoadShader(vertPath, fragPath);

        // TODO: Set projection matrix

        isInitialized = true;
    }

    void RenderState::ClearContext(const glm::vec4& color)
    {
        m_clearColor = color;
        glClearColor(V4_OPEN(m_clearColor));
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void RenderState::DrawMesh(Mesh& mesh, Shader& shader)
    {
        shader.Bind();
        mesh.vertexArray.Bind();

        glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, NULL);

        shader.Unbind();
    }
}
