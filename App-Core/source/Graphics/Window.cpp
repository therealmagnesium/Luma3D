#include "Graphics/Window.h"

#include "Core/Application.h"
#include "Core/Base.h"
#include "Core/Log.h"
#include "Core/Input.h"
#include "Core/Time.h"

#include "UI/UI.h"

#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <imgui.h>

namespace Graphics
{
    static void SetupSDL()
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        {
            FATAL("Failed to initialize SDL2!");
            Core::App->Quit();
            return;
        }

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    }

    Window CreateWindow(u32 width, u32 height, const char* title)
    {
        Window window;
        window.width = width;
        window.height = height;
        window.title = title;

        SetupSDL();

        s32 flags =
            SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI;
        window.handle =
            SDL_CreateWindow(window.title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                             window.width, window.height, flags);
        if (window.handle == NULL)
        {
            FATAL("Failed to create window!");
            Core::App->Quit();
            return window;
        }

        window.context = SDL_GL_CreateContext(window.handle);
        if (window.context == NULL)
        {
            FATAL("Failed to create the context for the window!");
            Core::App->Quit();
            return window;
        }

        SDL_GL_MakeCurrent(window.handle, window.context);
        gladLoadGL();

        if (window.isVsync)
            SDL_GL_SetSwapInterval(1);
        else
            SDL_GL_SetSwapInterval(0);

        return window;
    }

    void HandleWindowEvents(Window& window)
    {
        Core::UpdateTime();

        for (int i = 0; i < MOUSE_BUTTON_COUNT; i++)
            Core::Input.mouse.buttonsClicked[i] = false;

        for (int i = 0; i < KEY_COUNT; i++)
            Core::Input.keyboard.keysPressed[i] = false;

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            UI::ProcessEvent(&event);

            switch (event.type)
            {
                case SDL_QUIT:
                    INFO("Exiting out of application...");
                    Core::App->Quit();
                    break;

                case SDL_MOUSEMOTION:
                    Core::Input.mouse.position.x = event.motion.x;
                    Core::Input.mouse.position.y = event.motion.y;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    Core::Input.mouse.buttonsClicked[event.button.button] = true;
                    Core::Input.mouse.buttonsHeld[event.button.button] = true;
                    break;

                case SDL_MOUSEBUTTONUP:
                    Core::Input.mouse.buttonsClicked[event.button.button] = false;
                    Core::Input.mouse.buttonsHeld[event.button.button] = false;
                    break;

                case SDL_KEYDOWN:
                    Core::Input.keyboard.keysPressed[event.key.keysym.scancode] =
                        !Core::Input.keyboard.keysHeld[event.key.keysym.scancode];
                    Core::Input.keyboard.keysHeld[event.key.keysym.scancode] = true;
                    break;

                case SDL_KEYUP:
                    Core::Input.keyboard.keysPressed[event.key.keysym.scancode] = false;
                    Core::Input.keyboard.keysHeld[event.key.keysym.scancode] = false;
                    break;

                case SDL_WINDOWEVENT:
                {
                    switch (event.window.event)
                    {
                        case SDL_WINDOWEVENT_RESIZED:
                            window.width = event.window.data1;
                            window.height = event.window.data2;
                            Core::App->GetSpecification().windowWidth = window.width;
                            Core::App->GetSpecification().windowHeight = window.height;
                            glViewport(0, 0, window.width, window.height);
                            INFO("Resized window to %dx%d.", window.width, window.height);
                            break;

                        default:
                            break;
                    }
                }

                default:
                    break;
            }
        }

        if (Core::IsKeyDown(KEY_ESCAPE))
        {
            INFO("Exiting out of application...");
            Core::App->Quit();
        }

        ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);
        if (Core::IsMouseDown(MOUSE_BUTTON_LEFT))
            ImGui::SetMouseCursor(ImGuiMouseCursor_None);
    }

    void DestroyWindow(Window& window)
    {
        SDL_GL_DeleteContext(window.context);
        SDL_DestroyWindow(window.handle);
        SDL_Quit();
    }
}
