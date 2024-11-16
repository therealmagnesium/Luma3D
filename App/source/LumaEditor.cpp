#include "LumaEditor.h"
#include "glm/ext/matrix_transform.hpp"

#include <Core/Application.h>
#include <Core/Base.h>
#include <Core/Input.h>
#include <Core/Log.h>

#include <Graphics/Camera.h>
#include <Graphics/Mesh.h>
#include <Graphics/Renderer.h>
#include <Graphics/RendererInternal.h>
#include <Graphics/Shader.h>
#include <Graphics/Texture.h>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace Core;
using namespace Graphics;

static glm::mat4 model = glm::mat4(1.f);

void LumaEditor::OnCreate()
{
    Vertex vertices[4] = {
        {glm::vec3(-0.5f, -0.5f, 0.f), glm::vec3(0.f, 0.f, 1.f), glm::vec2(0.f, 0.f)}, // v0
        {glm::vec3(0.5f, -0.5f, 0.f), glm::vec3(0.f, 1.f, 0.f), glm::vec2(1.f, 0.f)},  // v1
        {glm::vec3(0.5f, 0.5f, 0.f), glm::vec3(1.f, 0.f, 0.f), glm::vec2(1.f, 1.f)},   // v2
        {glm::vec3(-0.5f, 0.5f, 0.f), glm::vec3(0.f, 1.f, 1.f), glm::vec2(0.f, 1.f)}   // v3
    };

    u32 indices[6] = {0, 1, 2, 2, 3, 0};

    m_camera = CreateCamera(glm::vec3(0.f, 0.f, 3.f), glm::vec3(0.f, 1.f, 0.f), 45.f);
    m_camera.moveSpeed = 2.f;
    SetPrimaryCamera(&m_camera);

    m_texture = LoadTexture("assets/textures/texel_checker.png", TEX_FMT_RGBA);
    m_mesh = LoadMesh(vertices, LEN(vertices), indices, LEN(indices));
    LogMeshInfo(m_mesh);

    model = glm::rotate(model, glm::radians(-45.f), glm::vec3(1.f, 0.f, 0.f));
}

void LumaEditor::OnShutdown()
{
    UnloadTexture(m_texture);
    UnloadMesh(m_mesh);
}

void LumaEditor::OnUpdate()
{
    UpdateCamera(CAMERA_FREE);

    if (IsKeyPressed(KEY_C))
        LogCameraInfo(m_camera);
}

void LumaEditor::OnRender()
{
    Renderer.defaultShader.Bind();
    Renderer.defaultShader.SetMat4(Renderer.defaultShader.uniformLocs[SHADER_LOC_MATRIX_MODEL],
                                   glm::value_ptr(model));
    Renderer.defaultShader.Unbind();

    m_texture.Bind(0);
    Renderer.DrawMesh(m_mesh, Renderer.defaultShader);
}
