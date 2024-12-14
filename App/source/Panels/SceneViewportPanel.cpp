#include "SceneViewportPanel.h"

void SceneViewportPanel::SetContext(Scene* scene)
{
    m_context = scene;
}

void SceneViewportPanel::Display()
{
    Framebuffer& framebuffer = App->GetFramebuffer();

    ImGui::Begin("Scene Viewport");
    {
        m_context->GetEditorCamera().isLocked = !ImGui::IsWindowHovered();

        u64 textureID = framebuffer.colorAttachment;
        ImVec2 aspectSize = this->GetLargestViewportSize();
        ImVec2 windowPosition = this->GetCenteredViewportPosition(aspectSize);

        ImGui::SetCursorPos(windowPosition);
        ImGui::Image((void*)textureID, aspectSize, ImVec2(0, 1), ImVec2(1, 0));
    }
    ImGui::End();
}

ImVec2 SceneViewportPanel::GetLargestViewportSize()
{
    ImVec2 windowSize = ImGui::GetContentRegionAvail();
    windowSize.x -= ImGui::GetScrollX();
    windowSize.y -= ImGui::GetScrollY();

    float aspectRatio = App->GetWindow().width / (float)App->GetWindow().height;
    ImVec2 aspect = ImVec2(windowSize.x, windowSize.x / aspectRatio);

    if (aspect.y > windowSize.y)
    {
        aspect.y = windowSize.y;
        aspect.x = aspect.y * aspectRatio;
    }

    return aspect;
}

ImVec2 SceneViewportPanel::GetCenteredViewportPosition(ImVec2 aspectSize)
{
    ImVec2 windowSize = ImGui::GetContentRegionAvail();
    windowSize.x -= ImGui::GetScrollX();
    windowSize.y -= ImGui::GetScrollY();

    ImVec2 viewportPosition;
    viewportPosition.x = (windowSize.x / 2.f) - (aspectSize.x / 2.f);
    viewportPosition.y = (windowSize.y / 2.f) - (aspectSize.y / 2.f);

    return viewportPosition;
}
