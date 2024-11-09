#pragma once
#include <Core/Application.h>
#include <Core/Base.h>

#include <Graphics/Mesh.h>
#include <Graphics/Shader.h>

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
    Mesh m_mesh;
};
