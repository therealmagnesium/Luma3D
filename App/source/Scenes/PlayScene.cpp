#include "PlayScene.h"

static Model model;

void PlayScene::OnCreate()
{
    Renderer.clearColor = glm::vec4(0.2f, 0.2f, 0.2f, 1.f);

    model = LoadModel("assets/models/cube.glb");

    m_camera = this->AddEntity("Main Camera");
    m_camera->AddComponent<TransformComponent>(glm::vec3(2.7f, 2.4f, 6.7f),
                                               glm::vec3(-110.8f, -21.4f, 0.f));
    m_camera->AddComponent<CameraComponent>(true);

    m_directionalLight = this->AddEntity("Directional Light");
    m_directionalLight->AddComponent<TransformComponent>(
        glm::vec3(0.f), glm::vec3(-15.f, -30.f, -20.f), glm::vec3(0.f));
    m_directionalLight->AddComponent<DirectionalLightComponent>(Renderer.defaultShader);

    m_player = this->AddEntity("Player");
    m_player->AddComponent<TransformComponent>(glm::vec3(0.f, 0.4f, 0.f), glm::vec3(0.f),
                                               glm::vec3(0.5f));
    auto& playerMC = m_player->AddComponent<ModelComponent>(model);
    playerMC.model.materials[0].diffuse = glm::vec3(0.9f, 0.1f, 0.1f);

    m_ground = this->AddEntity("Ground");
    m_ground->AddComponent<TransformComponent>(glm::vec3(0.f), glm::vec3(0.f),
                                               glm::vec3(1.f, 0.5f, 2.f));
    auto& groundMC = m_ground->AddComponent<ModelComponent>(model);
    groundMC.model.materials[0].diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
}

void PlayScene::OnShutdown()
{
    UnloadModel(model);
}

void PlayScene::OnUpdate()
{
    if (IsKeyPressed(KEY_F2))
        this->SetActive(!this->IsActive());
}

void PlayScene::OnRender()
{
}
