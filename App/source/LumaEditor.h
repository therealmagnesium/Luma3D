#pragma once
#include <Core/Application.h>
#include <Core/Base.h>

#include <Graphics/Camera.h>
#include <Graphics/Mesh.h>
#include <Graphics/Model.h>
#include <Graphics/Shader.h>
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
    Texture m_texture;
    Mesh m_mesh;
    Model m_model;
};
