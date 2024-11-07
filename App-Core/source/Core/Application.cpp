#include "Core/Application.h"
#include "Core/Base.h"
#include "Core/Log.h"
#include "Core/Time.h"

#include "Graphics/Renderer.h"
#include "Graphics/Window.h"

#include <glad/glad.h>

namespace Core
{
    static bool initialized = false;
    Application* App = NULL;

    Application::Application(const ApplicationSpecification& appInfo) : m_specification(appInfo)
    {
        if (initialized)
        {
            FATAL("Cannot initialize application more than once!");
            return;
        }

        App = this;
        m_isRunning = true;

        m_window = Graphics::CreateWindow(m_specification.windowWidth, m_specification.windowHeight,
                                          m_specification.name.c_str());
        Graphics::Renderer.Init();
        InitTimeState(60);

        initialized = true;
        INFO("Successfully initialized the core application!");
    }

    Application::~Application()
    {
        Graphics::DestroyWindow(m_window);
    }

    void Application::Run()
    {
        while (m_isRunning)
        {
            Graphics::HandleWindowEvents(m_window);
            this->OnUpdate();

            Graphics::Renderer.ClearContext(glm::vec4(0.08f, 0.1f, 0.12f, 1.f));

            this->OnRender();
            this->OnRenderUI();

            SDL_GL_SwapWindow(m_window.handle);
            UpdateTimeLate();
        }

        this->OnShutdown();
    }

    void Application::Quit()
    {
        m_isRunning = false;
    }
}
