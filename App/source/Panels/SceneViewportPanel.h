#pragma once
#include <Luma3D.h>
#include <imgui.h>

using namespace Core;
using namespace Graphics;

class SceneViewportPanel
{
public:
    SceneViewportPanel() = default;

    void SetContext(Scene* scene);
    void Display();

private:
    ImVec2 GetLargestViewportSize();
    ImVec2 GetCenteredViewportPosition(ImVec2 aspectSize);

private:
    Scene* m_context = NULL;
};
