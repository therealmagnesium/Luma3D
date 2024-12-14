#pragma once
#include "Scenes/PlayScene.h"
#include "Scenes/TestScene.h"
#include "Panels/SceneHeirarchyPanel.h"
#include "Panels/SceneViewportPanel.h"

#include <Luma3D.h>

using namespace Core;
using namespace Graphics;

class LumaEditor : public Application
{
public:
    LumaEditor(const ApplicationSpecification& appInfo);

    void OnRenderUI() override;

private:
    TestScene* m_testScene = NULL;
    PlayScene* m_playScene = NULL;
    SceneHeirarchyPanel m_sceneHeirarchyPanel;
    SceneViewportPanel m_sceneViewportPanel;
};
