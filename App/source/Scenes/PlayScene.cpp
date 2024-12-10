#include "PlayScene.h"

static Model model;

void PlayScene::OnCreate()
{
    Renderer.clearColor = glm::vec4(0.2f, 0.2f, 0.2f, 1.f);

    model = LoadModel("assets/models/cube.glb");
    model.materials[0].diffuse = glm::vec3(0.8f, 0.4f, 0.1f);

    m_camera = CreateCamera(glm::vec3(2.7f, 2.4f, 6.7f), glm::vec3(0.f, 1.f, 0.f), 45.f);
    m_camera.rotation = glm::vec3(-110.8f, -21.4f, 0.f);
    SetPrimaryCamera(&m_camera);

    m_entity = this->AddEntity("Directional Light");
    m_entity->AddComponent<TransformComponent>(glm::vec3(0.f), glm::vec3(-15.f, -30.f, -20.f),
                                               glm::vec3(0.f));
    m_entity->AddComponent<DirectionalLightComponent>(Renderer.defaultShader);

    m_entity = this->AddEntity("Ground");
    m_entity->AddComponent<TransformComponent>(glm::vec3(0.f), glm::vec3(0.f),
                                               glm::vec3(1.f, 0.5f, 2.f));
    m_entity->AddComponent<ModelComponent>(model);
}

void PlayScene::OnShutdown()
{
    UnloadModel(model);
}

void PlayScene::OnUpdate()
{
    UpdateCamera(CAMERA_FREE);

    if (IsKeyPressed(KEY_C))
        LogCameraInfo(m_camera);
}

void PlayScene::OnRender()
{
}
