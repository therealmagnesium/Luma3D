#include "LumaEditor.h"

#include <Core/Application.h>
#include <Core/Base.h>
#include <Core/Input.h>
#include <Core/Log.h>

#include <Graphics/Camera.h>
#include <Graphics/Mesh.h>
#include <Graphics/Model.h>
#include <Graphics/Renderer.h>
#include <Graphics/RendererInternal.h>
#include <Graphics/Shader.h>
#include <Graphics/Texture.h>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace Core;
using namespace Graphics;

void LumaEditor::OnCreate()
{
    m_camera = CreateCamera(glm::vec3(-2.8f, 2.5f, 5.f), glm::vec3(0.f, 1.f, 0.f), 45.f);
    m_camera.rotation = glm::vec3(-57.f, -20.f, 0.f);
    SetPrimaryCamera(&m_camera);

    m_model = LoadModel("assets/models/boxing_ring.obj");
    LogModelInfo(m_model);
}

void LumaEditor::OnShutdown()
{
    UnloadModel(m_model);
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

    Renderer.defaultShader.Unbind();

    Renderer.DrawModel(m_model, Renderer.defaultShader);
}
