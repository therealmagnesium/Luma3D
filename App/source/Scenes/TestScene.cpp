#include "TestScene.h"
#include <Luma3D.h>

void TestScene::OnCreate()
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
    m_model2 = LoadModel("assets/models/cube.glb");

    m_light = CreateDirectionalLight(&Renderer.defaultShader, glm::vec3(-0.1f, -0.8f, -0.4f),
                                     glm::vec3(0.8f, 0.8f, 0.6f), 10.f);
}

void TestScene::OnShutdown()
{
    UnloadModel(m_model);
    UnloadModel(m_model2);
    UnloadShader(m_skyboxShader);
    UnloadSkybox(m_skybox);
}

void TestScene::OnUpdate()
{
    UpdateDirectionalLight(m_light);
    UpdateCamera(CAMERA_FREE);
}

void TestScene::OnRender()
{
    Renderer.DrawModel(m_model, Renderer.defaultShader, glm::vec3(0.f), glm::vec3(0.f),
                       glm::vec3(2.f));
    Renderer.DrawModel(m_model2, Renderer.defaultShader, glm::vec3(5.f, 5.f, 0.f), glm::vec3(0.f),
                       glm::vec3(2.f));
    Renderer.DrawSkybox(m_skybox, m_skyboxShader);
}
