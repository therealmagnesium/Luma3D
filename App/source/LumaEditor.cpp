#include "LumaEditor.h"

#include <Luma3D.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

using namespace Core;
using namespace Graphics;

static bool editing = false;

void LumaEditor::OnCreate()
{
    m_camera = CreateCamera(glm::vec3(35.f, 40.f, 52.f), glm::vec3(0.f, 1.f, 0.f), 45.f);
    m_camera.moveSpeed = 40.f;
    m_camera.rotation = glm::vec3(-124.f, -19.f, -1.f);
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

    m_light = CreateDirectionalLight(&Renderer.defaultShader, glm::vec3(-1.f, -1.f, 0.f),
                                     glm::vec3(0.8f, 0.8f, 0.6f), 4.5f);
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

    if (IsKeyPressed(KEY_E))
        editing = !editing;

    m_camera.isLocked = editing;
}

void LumaEditor::OnRender()
{
    Renderer.DrawModel(m_model, Renderer.defaultShader, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f),
                       glm::vec3(3.f));
    Renderer.DrawSkybox(m_skybox, m_skyboxShader);
}

void LumaEditor::OnRenderUI()
{
    if (editing)
    {
        ImGui::Begin("Light Properties");
        {
            ImGui::DragFloat3("Direction", glm::value_ptr(m_light.direction), 0.02f, -1.f, 1.f);
            ImGui::ColorEdit3("Color", glm::value_ptr(m_light.color));
            ImGui::DragFloat("Intenstiy", &m_light.intensity, 0.02f, 0.1f, 100.f);
            ImGui::DragFloat("Roughness", &m_model.materials[0].roughness, 0.02f, 0.f, 1.f);
            ImGui::DragFloat("Metalic", &m_model.materials[0].metalic, 0.02f, 0.f, 1.f);
        }
        ImGui::End();

        ImGui::Begin("Camera Properties");
        {
            ImGui::Text("Position: " V3_FMT, V3_OPEN(m_camera.position));
            ImGui::Text("Rotation: " V3_FMT, V3_OPEN(m_camera.rotation));
            ImGui::Text("Target: " V3_FMT, V3_OPEN(m_camera.target));
            ImGui::Text("Direction: " V3_FMT, V3_OPEN(m_camera.direction));
            ImGui::Text("Up: " V3_FMT, V3_OPEN(m_camera.up));
            ImGui::Text("FOV: %.1f", m_camera.fov);
            ImGui::Text("Move speed: %.1f", m_camera.moveSpeed);
            ImGui::Text("Is locekd: %d", m_camera.isLocked);
        }
        ImGui::End();
    }
}
