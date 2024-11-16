#include "Graphics/Renderer.h"
#include "Graphics/Shader.h"
#include "Graphics/Texture.h"
#include "Graphics/Window.h"

#include "Core/Application.h"
#include "Core/Log.h"
#include "Core/Time.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
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

        Renderer.defaultShader.uniformLocs[SHADER_LOC_MATRIX_MODEL] =
            GetUniformLocation(Renderer.defaultShader, "model");

        Renderer.defaultShader.uniformLocs[SHADER_LOC_MATRIX_VIEW] =
            GetUniformLocation(Renderer.defaultShader, "view");

        Renderer.defaultShader.uniformLocs[SHADER_LOC_MATRIX_PROJECTION] =
            GetUniformLocation(Renderer.defaultShader, "projection");

        Renderer.defaultShader.Bind();

        Renderer.defaultShader.SetInt(Renderer.defaultShader.uniformLocs[SHADER_LOC_MAP_DIFFUSE],
                                      SHADER_LOC_MAP_DIFFUSE);

        Renderer.defaultShader.SetInt(Renderer.defaultShader.uniformLocs[SHADER_LOC_MAP_SPECULAR],
                                      SHADER_LOC_MAP_SPECULAR);

        Renderer.defaultShader.Unbind();

        TextureFormatsInit();

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

    void RendererBegin()
    {
        Renderer.clearColor = glm::vec4(0.08f, 0.1f, 0.12f, 1.f);
        Renderer.ClearContext(Renderer.clearColor);
    }
    void RendererEnd()
    {
        Window& window = Core::App->GetWindow();
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
    }

    void RenderState::DrawMesh(Mesh& mesh, Shader& shader)
    {
        Window& window = Core::App->GetWindow();
        float aspectRatio = (float)window.width / (float)window.height;
        Renderer.projection = glm::perspective(glm::radians(45.f), aspectRatio, 0.1f, 1000.f);

        shader.Bind();

        Renderer.defaultShader.SetMat4(Renderer.defaultShader.uniformLocs[SHADER_LOC_MATRIX_VIEW],
                                       glm::value_ptr(Renderer.primaryCamera->view));

        Renderer.defaultShader.SetMat4(
            Renderer.defaultShader.uniformLocs[SHADER_LOC_MATRIX_PROJECTION],
            glm::value_ptr(Renderer.projection));

        mesh.vertexArray.Bind();
        mesh.indexBuffer.Bind();

        glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, NULL);

        mesh.indexBuffer.Unbind();
        mesh.vertexArray.Unbind();
        shader.Unbind();
    }
}
