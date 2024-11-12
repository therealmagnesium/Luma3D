#include "Graphics/Renderer.h"
#include "Core/Log.h"
#include "Graphics/Shader.h"
#include "Graphics/Texture.h"

#include <glm/glm.hpp>
#include <glad/glad.h>

namespace Graphics
{
    RenderState Renderer;

    static bool isInitialized = false;

    void RendererInit()
    {
        if (isInitialized)
        {
            ERROR("Cannot initialize renderer more than once!");
            return;
        }

        const char* vertPath = "assets/shaders/Default_vs.glsl";
        const char* fragPath = "assets/shaders/Default_fs.glsl";
        Renderer.defaultShader = LoadShader(vertPath, fragPath);

        Renderer.defaultShader.uniformLocs[SHADER_LOC_MAP_DIFFUSE] =
            GetUniformLocation(Renderer.defaultShader, "texture0");

        Renderer.defaultShader.uniformLocs[SHADER_LOC_MAP_SPECULAR] =
            GetUniformLocation(Renderer.defaultShader, "texture1");

        Renderer.defaultShader.Bind();
        Renderer.defaultShader.SetInt(Renderer.defaultShader.uniformLocs[SHADER_LOC_MAP_DIFFUSE], 0);
        Renderer.defaultShader.SetInt(Renderer.defaultShader.uniformLocs[SHADER_LOC_MAP_SPECULAR], 1);
        Renderer.defaultShader.Unbind();

        TextureFormatsInit();

        // TODO: Set projection matrix

        isInitialized = true;
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

    void RenderState::ClearContext(const glm::vec4& color)
    {
        clearColor = color;
        glClearColor(V4_OPEN(clearColor));
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void RenderState::DrawMesh(Mesh& mesh, Shader& shader)
    {
        shader.Bind();
        mesh.vertexArray.Bind();
        mesh.indexBuffer.Bind();

        glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, NULL);

        shader.Unbind();
    }
}
