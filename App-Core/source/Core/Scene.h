#pragma once
#include "Core/Entity.h"
#include "Core/EntityManager.h"

#include "Graphics/Camera.h"

namespace Core
{
    class Scene
    {
    public:
        Scene()
        {
            m_entityManager.SetContext(this);
            m_editorCamera =
                Graphics::CreateCamera(glm::vec3(0.f, 1.f, 5.f), glm::vec3(0.f, 1.f, 0.f), 45.f);
            // Graphics::SetPrimaryCamera(&m_editorCamera);
        };
        virtual ~Scene() {}

        virtual void OnCreate() = 0;
        virtual void OnUpdate() = 0;
        virtual void OnRender() {}
        virtual void OnShutdown() {}

        inline bool IsActive() const { return m_isActive; }
        inline EntityManager& GetEntityManager() { return m_entityManager; }
        inline Graphics::Camera& GetEditorCamera() { return m_editorCamera; }

        inline void SetActive(bool active) { m_isActive = active; }
        inline std::shared_ptr<Entity> AddEntity(const char* tag)
        {
            return m_entityManager.AddEntity(tag);
        }

    private:
        bool m_isActive = false;
        EntityManager m_entityManager;
        Graphics::Camera m_editorCamera;
    };
}
