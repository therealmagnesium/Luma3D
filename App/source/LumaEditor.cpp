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
    m_camera = CreateCamera(glm::vec3(62.f, -5.f, 62.f), glm::vec3(0.f, 1.f, 0.f), 45.f);
    m_camera.moveSpeed = 40.f;
    m_camera.rotation = glm::vec3(-133.f, -1.f, 0.f);
    SetPrimaryCamera(&m_camera);

    const char* paths[] = {"assets/textures/skybox5/posx.png", "assets/textures/skybox5/negx.png",
                           "assets/textures/skybox5/posy.png", "assets/textures/skybox5/negy.png",
                           "assets/textures/skybox5/posz.png", "assets/textures/skybox5/negz.png"};

    m_skyboxShader = LoadShader("assets/shaders/Skybox_vs.glsl", "assets/shaders/Skybox_fs.glsl");
    m_skyboxShader.uniformLocs[SHADER_LOC_MAP_DIFFUSE] =
        GetUniformLocation(m_skyboxShader, "skybox");
    m_skyboxShader.uniformLocs[SHADER_LOC_MATRIX_VIEW] =
        GetUniformLocation(m_skyboxShader, "matView");
    m_skyboxShader.uniformLocs[SHADER_LOC_MATRIX_PROJECTION] =
        GetUniformLocation(m_skyboxShader, "matProjection");

    m_skybox = LoadSkybox(paths, LEN(paths), TEX_FMT_RGBA);

    m_model = LoadModel("assets/models/environment.obj");
    // m_model.materials[1].diffuse = glm::vec3(0.6f, 0.4f, 0.2f);

    m_light = CreateDirectionalLight(&Renderer.defaultShader, glm::vec3(0.7f, -0.9f, -0.8f),
                                     glm::vec3(0.8f, 0.8f, 0.6f), 1.75f);
}

void LumaEditor::OnShutdown()
{
    UnloadModel(m_model);
    UnloadShader(m_skyboxShader);
    UnloadSkybox(m_skybox);
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
    Renderer.DrawModel(m_model, Renderer.defaultShader, glm::vec3(0.f), glm::vec3(0.f),
                       glm::vec3(3.f));
    Renderer.DrawSkybox(m_skybox, m_skyboxShader);
}
