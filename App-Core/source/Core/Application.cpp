#include "Core/Application.h"
#include "Core/AssetManager.h"
#include "Core/Base.h"
#include "Core/Log.h"
#include "Core/Time.h"

#include "Graphics/Renderer.h"
#include "Graphics/Window.h"

#include "UI/UI.h"

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

        m_framebuffer =
            Graphics::CreateFramebuffer(m_specification.windowWidth, m_specification.windowHeight);

        TimeStateInit(60);
        Graphics::RendererInit();
        UI::SetupContext();

        initialized = true;
        INFO("Successfully initialized the core application!");
        INFO("GPU vendor - %s", glGetString(GL_VENDOR));
        INFO("Renderer - %s", glGetString(GL_RENDERER));
        INFO("OpenGL version - %s", glGetString(GL_VERSION));
    }

    Application::~Application()
    {
        AssetManager::Clean();
        UI::ShutdownContext();

        Graphics::RendererShutdown();
        Graphics::DeleteFramebuffer(m_framebuffer);
        Graphics::DestroyWindow(m_window);

        INFO("Successfully shutdown the core application!");
    }

    void Application::Run()
    {
        while (m_isRunning)
        {
            Graphics::HandleWindowEvents(m_window);

            this->OnUpdate();
            m_activeScene->GetEntityManager().Update();

            if (!m_activeScene->IsActive())
            {
                Graphics::SetPrimaryCamera(&m_activeScene->GetEditorCamera());
                Graphics::UpdateCameraFree(m_activeScene->GetEditorCamera());
                Graphics::UpdateCameraMatrix(m_activeScene->GetEditorCamera());
            }

            UI::BeginFrame();
            this->OnRenderUI();
            UI::EndFrame();

            Graphics::Renderer.ClearContext(0);
            m_framebuffer.Bind();

            Graphics::RendererBegin();
            m_activeScene->GetEntityManager().DrawEntities();

            m_framebuffer.Unbind();
            Graphics::RendererEnd();
        }
    }

    void Application::Quit()
    {
        INFO("Exiting out of the application...");
        m_isRunning = false;
    }

    std::shared_ptr<Scene>& Application::GetActiveScene()
    {
        return m_activeScene;
    }

    void Application::SetActiveScene(const std::shared_ptr<Scene>& scene)
    {
        m_activeScene = scene;
    }
}
