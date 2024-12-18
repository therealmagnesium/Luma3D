#include "PlayScene.h"

void PlayScene::OnCreate()
{
    Renderer.clearColor = glm::vec4(0.2f, 0.2f, 0.2f, 1.f);

    AssetManager::AddModel("Cube", "assets/models/cube.glb");
    AssetManager::AddModel("Kamek", "assets/models/kamek.fbx");
    Model cubeModel = AssetManager::GetModel("Cube");
    Model kamekModel = AssetManager::GetModel("Kamek");

    /*
    m_camera = this->AddEntity("Main Camera");
    m_camera->AddComponent<TransformComponent>(glm::vec3(2.7f, 2.4f, 6.7f),
                                               glm::vec3(-110.8f, -21.4f, 0.f));
    m_camera->AddComponent<CameraComponent>(true);

    m_directionalLight = this->AddEntity("Directional Light");
    m_directionalLight->AddComponent<TransformComponent>(
        glm::vec3(0.f), glm::vec3(-15.f, -30.f, -20.f), glm::vec3(0.f));
    m_directionalLight->AddComponent<DirectionalLightComponent>(Renderer.defaultShader);*/
}

void PlayScene::OnShutdown()
{
}

void PlayScene::OnUpdate()
{
    if (IsKeyPressed(KEY_F2))
        this->SetActive(!this->IsActive());
}

void PlayScene::OnRender()
{
}
