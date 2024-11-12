#include "LumaEditor.h"

#include <Core/Application.h>
#include <Core/Base.h>
#include <Core/Input.h>
#include <Core/Log.h>

#include <Graphics/Mesh.h>
#include <Graphics/Renderer.h>
#include <Graphics/RendererInternal.h>
#include <Graphics/Shader.h>
#include <Graphics/Texture.h>

#include <glad/glad.h>

using namespace Core;
using namespace Graphics;

LumaEditor::LumaEditor(const ApplicationSpecification& appInfo) : Application(appInfo)
{
    Vertex vertices[4] = {
        {glm::vec3(-0.5f, -0.5f, 0.f), glm::vec3(0.f, 0.f, 1.f), glm::vec2(0.f, 0.f)}, // v0
        {glm::vec3(0.5f, -0.5f, 0.f), glm::vec3(0.f, 1.f, 0.f), glm::vec2(1.f, 0.f)},  // v1
        {glm::vec3(0.5f, 0.5f, 0.f), glm::vec3(1.f, 0.f, 0.f), glm::vec2(1.f, 1.f)},   // v2
        {glm::vec3(-0.5f, 0.5f, 0.f), glm::vec3(0.f, 1.f, 1.f), glm::vec2(0.f, 1.f)}   // v3
    };

    u32 indices[6] = {0, 1, 2, 2, 3, 0};

    m_texture = LoadTexture("assets/textures/texel_checker.png", TEX_FMT_RGBA);
    m_texture2 = LoadTexture("assets/textures/small_checker.png", TEX_FMT_RGB);
    m_mesh = LoadMesh(vertices, LEN(vertices), indices, LEN(indices));
    LogMeshInfo(m_mesh);
}

void LumaEditor::OnShutdown()
{
    UnloadTexture(m_texture);
    UnloadTexture(m_texture2);
    UnloadMesh(m_mesh);
}

void LumaEditor::OnUpdate()
{
}

void LumaEditor::OnRender()
{
    m_texture.Bind(0);
    m_texture2.Bind(1);
    Renderer.DrawMesh(m_mesh, Renderer.defaultShader);
}
