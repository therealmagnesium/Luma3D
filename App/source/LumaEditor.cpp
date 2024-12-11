#include "LumaEditor.h"
#include "Scenes/TestScene.h"
#include "Scenes/PlayScene.h"

#include <Luma3D.h>
#include <imgui.h>

using namespace Core;
using namespace Graphics;

static bool editing = false;

LumaEditor::LumaEditor(const ApplicationSpecification& specification) : Application(specification)
{
    m_testScene = new TestScene();
    m_playScene = new PlayScene();

    this->AddScene(m_testScene, "Test");
    this->AddScene(m_playScene, "Play");

    this->SwitchToScene("Play");

    m_sceneHeirarchyPanel.SetContext(m_playScene);
}

void LumaEditor::OnRenderUI()
{
    if (IsKeyPressed(KEY_F1))
        editing = !editing;

    Scene* currentScene = this->GetCurrentScene();
    Camera& editorCamera = currentScene->GetEditorCamera();

    editorCamera.isLocked = editing;

    if (editing)
        m_sceneHeirarchyPanel.Display();
}
