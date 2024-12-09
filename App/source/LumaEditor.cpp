#include "LumaEditor.h"
#include "Scenes/TestScene.h"

#include <Luma3D.h>
#include <imgui.h>

using namespace Core;
using namespace Graphics;

static bool editing = false;

LumaEditor::LumaEditor(const ApplicationSpecification& specification) : Application(specification)
{
    this->AddScene(new TestScene(), "Test");
    this->SwitchToScene("Test");
}

void LumaEditor::OnRenderUI()
{
    ImGui::ShowDemoWindow();
}
