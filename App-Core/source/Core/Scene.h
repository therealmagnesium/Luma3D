#pragma once
#include "Core/Entity.h"
#include "Core/EntityManager.h"

namespace Core
{
    class Scene
    {
    public:
        Scene() = default;
        virtual ~Scene() {}

        virtual void OnCreate() = 0;
        virtual void OnUpdate() = 0;
        virtual void OnRender() {}
        virtual void OnShutdown() {}

        inline EntityManager& GetEntityManager() { return m_entityManager; }

        inline std::shared_ptr<Entity> AddEntity(const char* tag)
        {
            return m_entityManager.AddEntity(tag);
        }

    private:
        EntityManager m_entityManager;
    };
}
