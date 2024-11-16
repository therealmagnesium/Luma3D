#pragma once
#include "Core/Base.h"

namespace Core
{
    /*
     * [@brief] A representation of the global time state.
     * [@field] delta - The time it took between each frame in seconds.
     * [@field] now - The total time the application has been running in milliseconds.
     * [@field] last - The previous time of Time.now.
     * [@field] lastFrame - The previous frame count at the current time.
     * [@field] frameDelay - How much to delay each frame, based on the frame rate.
     * [@field] frameTime - The time it took between each frame in seconds.
     * [@field] frameRate - The amount of frames to render per second.
     * [@field] frameCount - The total number of frames that have been rendered.
     * */
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

    /*
     * [@brief] Initializes the time state, should only be called once by the core application.
     * [@param] frameRate - The target amount of frames to render per second.
     * */
    void TimeStateInit(u32 frameRate);

    // [@brief] Updates the time state, should be called before UpdateTimeLate()
    void UpdateTime();

    // [@brief] Delays how fast each frame is rendered if the framerate is larger than the target
    // frame rate.
    void UpdateTimeLate();
}
