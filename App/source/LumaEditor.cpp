#include "LumaEditor.h"
#include "Scenes/TestScene.h"
#include "Scenes/PlayScene.h"

#include <Luma3D.h>
#include <imgui.h>

using namespace Core;
using namespace Graphics;

LumaEditor::LumaEditor(const ApplicationSpecification& specification) : Application(specification)
{
    m_testScene = new TestScene();
    m_playScene = new PlayScene();

    this->AddScene(m_testScene, "Test");
    this->AddScene(m_playScene, "Play");

    this->SwitchToScene("Play");

    m_sceneHeirarchyPanel.SetContext(m_playScene);
    m_sceneViewportPanel.SetContext(m_playScene);

    m_sceneSerializer.SetContext(m_playScene);
}

void LumaEditor::OnRenderUI()
{
    ImGui::DockSpaceOverViewport();
    Scene* currentScene = this->GetCurrentScene();
    Camera& editorCamera = currentScene->GetEditorCamera();

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Save"))
                m_sceneSerializer.Serialize("scenes/PlayScene.luma");

            if (ImGui::MenuItem("Load"))
                m_sceneSerializer.Deserialize("scenes/PlayScene.luma");

            if (ImGui::MenuItem("Exit"))
                this->Quit();

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

    m_sceneHeirarchyPanel.Display();
    m_sceneViewportPanel.Display();
}
