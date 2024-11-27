#pragma once
#include <Core/Application.h>
#include <Core/Base.h>

#include <Graphics/Camera.h>
#include <Graphics/Light.h>
#include <Graphics/Mesh.h>
#include <Graphics/Model.h>
#include <Graphics/Shader.h>
#include <Graphics/Skybox.h>
#include <Graphics/RendererInternal.h>
#include <Graphics/Texture.h>

using namespace Core;
using namespace Graphics;

class LumaEditor : public Application
{
public:
    LumaEditor(const ApplicationSpecification& appInfo) : Application(appInfo) {}

    void OnCreate() override;
    void OnUpdate() override;
    void OnRender() override;
    void OnShutdown() override;

private:
    Camera m_camera;
    DirectionalLight m_light;
    Model m_model;
    Shader m_skyboxShader;
    Skybox m_skybox;
};
