#include "LumaEditor.h"

#include <Core/Application.h>
#include <Core/Base.h>
#include <Core/Input.h>
#include <Core/Log.h>

#include <Graphics/Camera.h>
#include <Graphics/Light.h>
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
    m_camera = CreateCamera(glm::vec3(-15.f, 9.f, 18.f), glm::vec3(0.f, 1.f, 0.f), 45.f);
    m_camera.moveSpeed = 20.f;
    m_camera.rotation = glm::vec3(-57.f, -20.f, 0.f);
    SetPrimaryCamera(&m_camera);

    m_model = LoadModel("assets/models/boxing_ring.obj");
    m_model2 = LoadModel("assets/models/boat.obj");

    m_light = CreateDirectionalLight(&Renderer.defaultShader, glm::vec3(0.3f, -0.5f, -0.8f),
                                     glm::vec3(0.8f, 0.8f, 0.6f), 2.f);
}

void LumaEditor::OnShutdown()
{
    UnloadModel(m_model);
    UnloadModel(m_model2);
}

void LumaEditor::OnUpdate()
{
    UpdateDirectionalLight(m_light);
    UpdateCamera(CAMERA_FREE);

    if (IsKeyPressed(KEY_C))
        LogCameraInfo(m_camera);
}

void LumaEditor::OnRender()
{
    Renderer.DrawModel(m_model, Renderer.defaultShader);
    Renderer.DrawModel(m_model2, Renderer.defaultShader);
}
