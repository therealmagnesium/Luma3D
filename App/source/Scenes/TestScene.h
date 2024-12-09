#pragma once
#include <Luma3D.h>

using namespace Core;
using namespace Graphics;

class TestScene : public Scene
{
public:
    TestScene() = default;

    void OnCreate() override;
    void OnUpdate() override;
    void OnRender() override;
    void OnShutdown() override;

private:
    Camera m_camera;
    DirectionalLight m_light;
    Model m_model;
    Model m_model2;
    Shader m_skyboxShader;
    Skybox m_skybox;
};
