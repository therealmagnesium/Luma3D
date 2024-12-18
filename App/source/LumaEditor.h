#pragma once
#include "Panels/SceneHeirarchyPanel.h"
#include "Panels/SceneViewportPanel.h"

#include <Luma3D.h>

using namespace Core;
using namespace Graphics;

class LumaEditor : public Application
{
public:
    LumaEditor(const ApplicationSpecification& appInfo);

    void OnUpdate() override;
    void OnRenderUI() override;

private:
    void CreateNewScene();
    void OpenSceneDialog();
    void SaveSceneDialog();

private:
    std::shared_ptr<Scene> m_activeScene = NULL;
    SceneHeirarchyPanel m_sceneHeirarchyPanel;
    SceneViewportPanel m_sceneViewportPanel;
    SceneSerializer m_sceneSerializer;
};
