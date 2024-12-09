#pragma once
#include "Core/Base.h"

#include <SDL2/SDL.h>
#include <string>

namespace Graphics
{
    /*
     * @brief A window that can be rendered to.
     * @field width - The width of the window.
     * @field height - The height of the window.
     * @field title - The title of the window.
     * @field isVsync - If true, vsync will be enabled.
     * @field context - Where everything gets drawn to.
     * @field handle - The handle to the SDL_Window*.
     * */
    struct Window
    {
        u32 width;
        u32 height;
        std::string title;
        bool isVsync = true;
        void* context = NULL;
        SDL_Window* handle = NULL;
    };

    /*
     * @brief Create a window that can be rendered to.
     * @param[in] width - The width of the window.
     * @param[in] height - The height of the window.
     * @param[in] title - The title of the window.
     * */
    Window CreateWindow(u32 width, u32 height, const char* title);

    /*
     * @brief Handle all the events for a given window.
     * @param[in] window - The window to poll events from.
     * */
    void HandleWindowEvents(Window& window);

    /*
     * @brief Free the allocations made by the given window
     * @param[in] window - The window to destroy.
     */
    void DestroyWindow(Window& window);
}
