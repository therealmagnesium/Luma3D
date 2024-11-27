#pragma once
#include "Core/Base.h"
#include <SDL2/SDL_events.h>

namespace UI
{
    void SetupContext();
    void ShutdownContext();
    void ProcessEvent(SDL_Event* event);
    void BeginFrame();
    void EndFrame();
    void RenderFrame();
}
