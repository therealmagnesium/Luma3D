#include "SceneHeirarchyPanel.h"
#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

using namespace Core;
using namespace Graphics;

template <typename T, typename UIFunc>
static void DrawComponent(const char* name, std::shared_ptr<Entity>& entity, UIFunc uiFunction)
{
    const ImGuiTreeNodeFlags treeNodeFlags =
        ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed |
        ImGuiTreeNodeFlags_SpanFullWidth | ImGuiTreeNodeFlags_AllowItemOverlap;
    if (entity->HasComponent<T>())
    {
        auto& component = entity->GetComponent<T>();
        ImVec2 availableRegion = ImGui::GetContentRegionAvail();

        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4.f, 4.f));
        float lineHeight = ImGui::GetFont()->FontSize + ImGui::GetStyle().FramePadding.y * 2.f;
        ImGui::PopStyleVar();

        bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), treeNodeFlags, "%s", name);
        ImGui::SameLine(availableRegion.x - lineHeight * .5f);

        if (ImGui::Button("+", ImVec2(20.f, 20.f)))
            ImGui::OpenPopup("Component Settings");

        bool removeComponent = false;
        if (ImGui::BeginPopup("Component Settings"))
        {
            if (ImGui::MenuItem("Remove component"))
                removeComponent = true;

            ImGui::EndPopup();
        }

        if (open)
        {
            uiFunction(component);
            ImGui::TreePop();
        }

        if (removeComponent)
            entity->RemoveComponent<T>();
    }
}

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
        {
            this->DrawComponents(m_selectionContext);
        }
    }
    ImGui::End();

    ImGui::ShowDemoWindow();
}

void SceneHeirarchyPanel::DrawEntityNode(std::shared_ptr<Entity>& entity)
{
    EntityManager& entityManager = m_context->GetEntityManager();
    ImGuiTreeNodeFlags flags = ((entity == m_selectionContext) ? ImGuiTreeNodeFlags_Selected : 0) |
                               ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanFullWidth;
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

    if (ImGui::InputText("##Tag", buffer, sizeof(buffer)))
        entity->SetTag(buffer);

    ImGui::SameLine();
    ImGui::PushItemWidth(-1.f);

    if (ImGui::Button("Add Component"))
        ImGui::OpenPopup("Add Component");

    if (ImGui::BeginPopup("Add Component"))
    {
        if (ImGui::MenuItem("Transform"))
        {
            m_selectionContext->AddComponent<TransformComponent>();
            ImGui::CloseCurrentPopup();
        }

        if (ImGui::MenuItem("Model"))
        {
            m_selectionContext->AddComponent<ModelComponent>();
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
    ImGui::PopItemWidth();

    DrawComponent<TransformComponent>("Transform", entity, [&](auto& component) {
        ImGui::DragFloat3("Position", glm::value_ptr(component.position), 0.1f);
        ImGui::DragFloat3("Rotation", glm::value_ptr(component.rotation), 0.1f);
        ImGui::DragFloat3("Scale", glm::value_ptr(component.scale), 0.1f);
    });

    DrawComponent<ModelComponent>("Model", entity, [&](auto& component) {
        const char* names[AssetManager::GetModelCount()];
        AssetManager::GetAllModelNames(names);

        if (ImGui::Button("Select Model"))
            ImGui::OpenPopup("Select Model");

        ImGui::SameLine();
        ImGui::Text("%s", (component.model.name.empty()) ? "None" : component.model.name.c_str());

        if (ImGui::BeginPopup("Select Model"))
        {
            for (u32 i = 0; i < LEN(names); i++)
                if (ImGui::Selectable(names[i]))
                    component.model = AssetManager::GetModel(names[i]);

            ImGui::EndPopup();
        }

        ImGui::ColorEdit3("Tint", glm::value_ptr(component.tint));
    });

    DrawComponent<DirectionalLightComponent>("Directional Light", entity, [&](auto& component) {
        ImGui::DragFloat("Intensity", &component.light.intensity, 0.1f);
        ImGui::ColorEdit3("Color", glm::value_ptr(component.light.color));
    });

    DrawComponent<CameraComponent>("Camera", entity, [&](auto& component) {
        ImGui::Checkbox("Primary?", &component.isPrimary);
        ImGui::Checkbox("Locked?", &component.camera.isLocked);
        ImGui::DragFloat("Move Speed", &component.camera.moveSpeed);
        ImGui::DragFloat("FOV", &component.camera.fov);
        ImGui::ColorEdit3("Clear color", glm::value_ptr(Renderer.clearColor));
    });
}
