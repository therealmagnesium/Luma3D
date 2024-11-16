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
        TimeStateInit(60);
        Graphics::RendererInit();

        initialized = true;
        INFO("Successfully initialized the core application!");
        INFO("GPU vendor - %s", glGetString(GL_VENDOR));
        INFO("Renderer - %s", glGetString(GL_RENDERER));
        INFO("OpenGL version - %s", glGetString(GL_VERSION));
    }

    Application::~Application()
    {
        Graphics::RendererShutdown();
        Graphics::DestroyWindow(m_window);
        INFO("Successfully shutdown the core application!");
    }

    void Application::Run()
    {
        this->OnCreate();
        if (Graphics::Renderer.primaryCamera == NULL)
        {
            FATAL("Cannot run application because no primary camera is set!");
            this->Quit();
        }

        while (m_isRunning)
        {
            Graphics::HandleWindowEvents(m_window);
            this->OnUpdate();

            Graphics::RendererBegin();

            this->OnRender();
            this->OnRenderUI();

            Graphics::RendererEnd();
        }

        this->OnShutdown();
    }

    void Application::Quit()
    {
        m_isRunning = false;
    }
}
