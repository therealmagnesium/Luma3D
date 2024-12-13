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

        if (m_selectionContext == NULL)
        {
            if (ImGui::BeginPopupContextWindow())
            {
                if (ImGui::MenuItem("Create Empty Entity"))
                    entityManager.AddEntity("Entity");

                ImGui::EndPopup();
            }
        }
    }
    ImGui::End();

    ImGui::Begin("Properties Panel");
    {
        if (m_selectionContext != NULL)
            this->DrawComponents(m_selectionContext);

        if (ImGui::Button("Add Component"))
            ImGui::OpenPopup("Add Component");

        if (ImGui::BeginPopup("Add Component"))
        {
            if (ImGui::MenuItem("Transform"))
            {
                m_selectionContext->AddComponent<TransformComponent>();
                ImGui::CloseCurrentPopup();
            }

            if (ImGui::MenuItem("Camera"))
            {
                m_selectionContext->AddComponent<CameraComponent>(false);
                ImGui::CloseCurrentPopup();
            }

            if (ImGui::MenuItem("Directional Light"))
            {
                m_selectionContext->AddComponent<DirectionalLightComponent>(Renderer.defaultShader);
                ImGui::CloseCurrentPopup();
            }

            ImGui::EndPopup();
        }
    }
    ImGui::End();

    ImGui::ShowDemoWindow();
}

void SceneHeirarchyPanel::DrawEntityNode(std::shared_ptr<Entity>& entity)
{
    EntityManager& entityManager = m_context->GetEntityManager();
    ImGuiTreeNodeFlags flags = ((entity == m_selectionContext) ? ImGuiTreeNodeFlags_Selected : 0) |
                               ImGuiTreeNodeFlags_OpenOnArrow;
    bool isOpen = ImGui::TreeNodeEx((void*)entity->GetID(), flags, "%s", entity->GetTag());

    if (ImGui::IsItemClicked())
        m_selectionContext = entity;

    bool entityDeleted = false;
    if (ImGui::BeginPopupContextItem())
    {
        if (ImGui::MenuItem("Delete Entity"))
            entityDeleted = true;

        ImGui::EndPopup();
    }

    if (isOpen)
        ImGui::TreePop();

    if (entityDeleted)
    {
        entityManager.DestroyEntity(m_selectionContext);
        m_selectionContext = NULL;
    }
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

            static s32 selectedModel = -1;
            const char* names[AssetManager::GetModelCount()];
            AssetManager::GetAllModelNames(names);

            if (ImGui::Button("Select Model"))
                ImGui::OpenPopup("Select Model");

            ImGui::SameLine();
            ImGui::Text("%s", (selectedModel == -1) ? "None" : names[selectedModel]);

            if (ImGui::BeginPopup("Select Model"))
            {
                for (u32 i = 0; i < LEN(names); i++)
                    if (ImGui::Selectable(names[i]))
                    {
                        selectedModel = i;
                        mc.model = AssetManager::GetModel(names[i]);
                    }
                ImGui::EndPopup();
            }

            ImGui::TreePop();
        }
    }

    if (entity->HasComponent<DirectionalLightComponent>())
    {
        if (ImGui::TreeNodeEx((void*)typeid(DirectionalLightComponent).hash_code(),
                              ImGuiTreeNodeFlags_DefaultOpen, "Directional Light"))
        {
            auto& dlc = entity->GetComponent<DirectionalLightComponent>();
            ImGui::DragFloat("Intensity", &dlc.light.intensity, 0.1f);
            ImGui::ColorPicker3("Color", glm::value_ptr(dlc.light.color));

            ImGui::TreePop();
        }
    }

    if (entity->HasComponent<CameraComponent>())
    {
        if (ImGui::TreeNodeEx((void*)typeid(CameraComponent).hash_code(),
                              ImGuiTreeNodeFlags_DefaultOpen, "Camera"))
        {
            auto& cc = entity->GetComponent<CameraComponent>();
            ImGui::Checkbox("Primary?", &cc.isPrimary);
            ImGui::Checkbox("Locked?", &cc.camera.isLocked);
            ImGui::DragFloat("Move Speed", &cc.camera.moveSpeed);
            ImGui::DragFloat("FOV", &cc.camera.fov);

            ImGui::TreePop();
        }
    }
}
