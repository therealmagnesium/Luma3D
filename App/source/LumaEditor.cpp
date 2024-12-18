#include "LumaEditor.h"

#include <Luma3D.h>
#include <imgui.h>
#include <nfd.h>

using namespace Core;
using namespace Graphics;

LumaEditor::LumaEditor(const ApplicationSpecification& specification) : Application(specification)
{
    Renderer.clearColor = glm::vec4(0.2f, 0.2f, 0.2f, 1.f);

    AssetManager::AddModel("Cube", "assets/models/cube.glb");
    AssetManager::AddModel("Kamek", "assets/models/kamek.fbx");

    m_activeScene = std::make_shared<Scene>();
    this->SetActiveScene(m_activeScene);

    m_sceneSerializer.SetContext(m_activeScene.get());
    m_sceneHeirarchyPanel.SetContext(m_activeScene.get());
    m_sceneViewportPanel.SetContext(m_activeScene.get());
}

void LumaEditor::OnUpdate()
{
    std::shared_ptr<Scene>& scene = this->GetActiveScene();
    if (IsKeyPressed(KEY_F2))
        scene->SetActive(!scene->IsActive());

    if (IsKeyDown(KEY_LEFT_CTRL))
    {
        if (IsKeyPressed(KEY_N))
            this->CreateNewScene();

        else if (IsKeyPressed(KEY_O))
            this->OpenSceneDialog();

        else if (IsKeyPressed(KEY_S))
            this->SaveSceneDialog();
    }
}

void LumaEditor::OnRenderUI()
{
    ImGui::DockSpaceOverViewport();
    std::shared_ptr<Scene>& scene = this->GetActiveScene();
    Camera& editorCamera = scene->GetEditorCamera();

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New", "Ctrl+N"))
                this->CreateNewScene();

            if (ImGui::MenuItem("Save", "Ctrl+S"))
                this->SaveSceneDialog();

            if (ImGui::MenuItem("Load", "Ctrl+O"))
                this->OpenSceneDialog();

            if (ImGui::MenuItem("Exit"))
                this->Quit();

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

    m_sceneHeirarchyPanel.Display();
    m_sceneViewportPanel.Display();
}

void LumaEditor::CreateNewScene()
{
    m_activeScene = std::make_shared<Scene>();
    this->SetActiveScene(m_activeScene);

    m_sceneHeirarchyPanel.SetContext(m_activeScene.get());
    m_sceneViewportPanel.SetContext(m_activeScene.get());
}

void LumaEditor::OpenSceneDialog()
{
    std::string path = FileDialogs::OpenFile("luma", "scenes/");

    if (!path.empty())
    {
        this->CreateNewScene();

        m_sceneSerializer.SetContext(m_activeScene.get());
        m_sceneSerializer.Deserialize(path.c_str());
    }
}

void LumaEditor::SaveSceneDialog()
{
    std::string path = FileDialogs::SaveFile("luma", "scenes/");

    if (!path.empty())
    {
        m_sceneSerializer.SetContext(m_activeScene.get());
        m_sceneSerializer.Serialize(path.c_str());
    }
}
