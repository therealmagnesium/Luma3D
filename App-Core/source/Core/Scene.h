#pragma once
#include "Core/Base.h"
#include <string>

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

    private:
    };
}
