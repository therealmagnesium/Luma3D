#pragma once
#include "Core/Base.h"

namespace Core
{
    struct TimeState
    {
        float delta;
        float now;
        float last;

        float lastFrame;
        float frameDelay;
        float frameTime;

        u32 frameRate;
        u32 frameCount;
    };

    extern TimeState Time;

    void TimeStateInit(u32 frameRate);
    void UpdateTime();
    void UpdateTimeLate();
}
