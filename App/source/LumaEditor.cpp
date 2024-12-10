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
    this->AddScene(new TestScene(), "Test");
    this->AddScene(new PlayScene(), "Play");

    this->SwitchToScene("Play");
}

void LumaEditor::OnRenderUI()
{
    EntityManager& entityManager = this->GetCurrentScene()->GetEntityManager();

    if (IsKeyPressed(KEY_E))
        editing = !editing;

    Renderer.primaryCamera->isLocked = editing;

    if (editing)
    {
        ImGui::Begin("Scene Heirarchy Panel");
        {
            for (auto& entity : entityManager.GetEntities())
            {
                const char* tag = entity->GetTag();
                ImGui::Text("%s", tag);
            }
        }
        ImGui::End();
    }
}
