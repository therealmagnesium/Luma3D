#pragma once
#include "Core/Base.h"
#include "Core/Components.h"
#include "Core/Entity.h"

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

namespace Core
{
    class Scene; // Forward declaration
    typedef std::vector<std::shared_ptr<Entity>> EntityVec;
    typedef std::unordered_map<std::string, EntityVec> EntityMap;

    class EntityManager
    {
    public:
        EntityManager() = default;
        std::shared_ptr<Entity> AddEntity(const char* tag);
        void Update();
        void DrawEntities();

        inline u64 GetEntityCount() { return m_totalEntities; }

        EntityVec& GetEntities();
        EntityVec& GetEntities(const char* tag);

        inline void SetContext(Scene* scene) { m_context = scene; }

    private:
        u64 m_totalEntities = 0;
        EntityVec m_entities;
        EntityVec m_toAdd;
        EntityMap m_entityMap;
        Scene* m_context = NULL;
    };
}
