#include "Core/EntityManager.h"
#include "Core/Components.h"
#include "Core/Log.h"
#include "Core/Scene.h"

#include "Graphics/Renderer.h"

#include <assert.h>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Core
{
    std::shared_ptr<Entity> EntityManager::AddEntity(const char* tag)
    {
        std::shared_ptr<Entity> entity = std::make_shared<Entity>(m_totalEntities++, tag);
        entity->AddComponent<TransformComponent>();
        entity->SetActive(true);
        m_toAdd.push_back(entity);
        return entity;
    }

    void EntityManager::DestroyEntity(std::shared_ptr<Entity>& entity)
    {
        auto entityIndex = std::find(m_entities.begin(), m_entities.end(), entity);
        if (entityIndex == m_entities.end())
            return;

        entity->SetActive(false);
        m_toDestroy.push_back(entity);
    }

    void EntityManager::Update()
    {
        assert(m_context != NULL);

        for (auto& entity : m_toAdd)
        {
            const char* entityTag = entity->GetTag();
            m_entities.push_back(entity);
            // m_entityMap[entityTag].push_back(entity);
        }

        for (u64 i = 0; i < m_toDestroy.size(); i++)
        {
            auto& entity = m_toDestroy[i];

            m_entities.erase(m_entities.begin() + entity->GetID());
            /*
                m_entityMap[entity->GetTag()].erase(m_entityMap[entity->GetTag()].begin() +
                                                    entity->GetID());*/
        }

        for (u64 i = 0; i < m_entities.size(); i++)
        {
            auto& entity = m_entities[i];
            const char* entityTag = entity->GetTag();
            if (!entity->IsAlive())
            {
                m_entities.erase(m_entities.begin() + i);
                // m_entityMap[entityTag].erase(m_entityMap[entityTag].begin() + i);
            }
        }

        m_toAdd.clear();
        m_toDestroy.clear();

        for (u64 i = 0; i < m_entities.size(); i++)
        {
            auto& entity = m_entities[i];
            if (entity->HasComponent<TransformComponent>() &&
                entity->HasComponent<ModelComponent>())
            {
                auto& tc = entity->GetComponent<TransformComponent>();
                auto& mc = entity->GetComponent<ModelComponent>();

                mc.model.transform = glm::mat4(1.f);
                mc.model.transform = glm::translate(mc.model.transform, tc.position);
                mc.model.transform = glm::rotate(mc.model.transform, glm::radians(tc.rotation.x),
                                                 glm::vec3(1.f, 0.f, 0.f));
                mc.model.transform = glm::rotate(mc.model.transform, glm::radians(tc.rotation.y),
                                                 glm::vec3(0.f, 1.f, 0.f));
                mc.model.transform = glm::rotate(mc.model.transform, glm::radians(tc.rotation.z),
                                                 glm::vec3(1.f, 0.f, 1.f));
                mc.model.transform = glm::scale(mc.model.transform, tc.scale);
            }

            if (entity->HasComponent<TransformComponent>() &&
                entity->HasComponent<DirectionalLightComponent>())
            {
                auto& tc = entity->GetComponent<TransformComponent>();
                auto& dlc = entity->GetComponent<DirectionalLightComponent>();
                dlc.light.direction = glm::normalize(tc.rotation);

                Graphics::UpdateDirectionalLight(dlc.light, dlc.shader);
            }

            if (entity->HasComponent<TransformComponent>() &&
                entity->HasComponent<CameraComponent>())
            {
                auto& tc = entity->GetComponent<TransformComponent>();
                auto& cc = entity->GetComponent<CameraComponent>();

                cc.camera.position = tc.position;
                cc.camera.rotation = tc.rotation;

                if (cc.isPrimary && m_context->IsActive())
                {
                    Graphics::SetPrimaryCamera(&cc.camera);
                    Graphics::UpdateCameraMatrix(cc.camera);
                }
            }
        }
    }

    void EntityManager::DrawEntities()
    {
        assert(m_context != NULL);

        for (u64 i = 0; i < m_entities.size(); i++)
        {
            auto& entity = m_entities[i];
            if (entity->HasComponent<TransformComponent>() &&
                entity->HasComponent<ModelComponent>())
            {
                TransformComponent& tc = entity->GetComponent<TransformComponent>();
                ModelComponent& mc = entity->GetComponent<ModelComponent>();

                if (entity->IsActive())
                    Graphics::Renderer.DrawModel(mc.model, Graphics::Renderer.defaultShader,
                                                 mc.tint);
            }
        }
    }

    EntityVec& EntityManager::GetEntities()
    {
        return m_entities;
    }

    EntityVec& EntityManager::GetEntities(const char* tag)
    {
        return m_entityMap[tag];
    }
}
