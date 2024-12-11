#include "SceneHeirarchyPanel.h"
#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

using namespace Core;
using namespace Graphics;

void SceneHeirarchyPanel::SetContext(Scene* scene)
{
    m_context = scene;
}

void SceneHeirarchyPanel::Display()
{
    EntityManager& entityManager = m_context->GetEntityManager();

    ImGui::Begin("Scene Heirarchy Panel");
    {
        for (auto& entity : entityManager.GetEntities())
            this->DrawEntityNode(entity);

        if (ImGui::IsWindowHovered() && IsMouseClicked(MOUSE_BUTTON_LEFT))
            m_selectionContext = NULL;
    }
    ImGui::End();

    ImGui::Begin("Properties Panel");
    {
        if (m_selectionContext != NULL)
            this->DrawComponents(m_selectionContext);
    }
    ImGui::End();
}

void SceneHeirarchyPanel::DrawEntityNode(std::shared_ptr<Entity>& entity)
{
    ImGuiTreeNodeFlags flags = ((entity == m_selectionContext) ? ImGuiTreeNodeFlags_Selected : 0) |
                               ImGuiTreeNodeFlags_OpenOnArrow;
    bool isOpen = ImGui::TreeNodeEx((void*)entity->GetID(), flags, "%s", entity->GetTag());

    if (ImGui::IsItemClicked())
        m_selectionContext = entity;

    if (isOpen)
        ImGui::TreePop();
}

void SceneHeirarchyPanel::DrawComponents(std::shared_ptr<Entity>& entity)
{
    char buffer[256];
    memset(buffer, 0, sizeof(buffer));
    strncpy(buffer, entity->GetTag(), sizeof(buffer));

    if (ImGui::InputText("Tag", buffer, sizeof(buffer)))
        entity->SetTag(buffer);

    if (entity->HasComponent<TransformComponent>())
    {
        if (ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(),
                              ImGuiTreeNodeFlags_DefaultOpen, "Transform"))
        {
            auto& tc = entity->GetComponent<TransformComponent>();
            ImGui::DragFloat3("Position", glm::value_ptr(tc.position), 0.1f);
            ImGui::DragFloat3("Rotation", glm::value_ptr(tc.rotation), 0.1f);
            ImGui::DragFloat3("Scale", glm::value_ptr(tc.scale), 0.1f);

            ImGui::TreePop();
        }
    }

    if (entity->HasComponent<ModelComponent>())
    {
        if (ImGui::TreeNodeEx((void*)typeid(ModelComponent).hash_code(),
                              ImGuiTreeNodeFlags_DefaultOpen, "Model"))
        {
            auto& mc = entity->GetComponent<ModelComponent>();

            ImGui::TreePop();
        }
    }

    if (entity->HasComponent<DirectionalLightComponent>())
    {
        if (ImGui::TreeNodeEx((void*)typeid(DirectionalLightComponent).hash_code(),
                              ImGuiTreeNodeFlags_DefaultOpen, "Directional Light"))
        {
            auto& dlc = entity->GetComponent<DirectionalLightComponent>();
            ImGui::DragFloat("Intensity", &dlc.light.intensity);
            ImGui::ColorPicker3("Color", glm::value_ptr(dlc.light.color));

            ImGui::TreePop();
        }
    }
}
