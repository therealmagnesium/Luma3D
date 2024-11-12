#pragma once
#include <Core/Application.h>
#include <Core/Base.h>

#include <Graphics/Mesh.h>
#include <Graphics/Shader.h>
#include <Graphics/Texture.h>

using namespace Core;
using namespace Graphics;

class LumaEditor : public Application
{
public:
    LumaEditor(const ApplicationSpecification& appInfo);

    void OnUpdate() override;
    void OnRender() override;
    void OnShutdown() override;

private:
    Texture m_texture;
    Texture m_texture2;
    Mesh m_mesh;
};
