#include "Core/Application.h"
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
    static std::string selectedSceneName;

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
        UI::SetupContext();

        initialized = true;
        INFO("Successfully initialized the core application!");
        INFO("GPU vendor - %s", glGetString(GL_VENDOR));
        INFO("Renderer - %s", glGetString(GL_RENDERER));
        INFO("OpenGL version - %s", glGetString(GL_VERSION));
    }

    Application::~Application()
    {
        for (auto& [name, scene] : m_scenesMap)
        {
            if (scene != NULL)
            {
                INFO("Deleting scene '%s'...", name.c_str());
                scene->OnShutdown();
                delete scene;
                scene = NULL;
            }
        }

        UI::ShutdownContext();
        Graphics::RendererShutdown();
        Graphics::DestroyWindow(m_window);
        INFO("Successfully shutdown the core application!");
    }

    void Application::Run()
    {
        if (Graphics::Renderer.primaryCamera == NULL)
        {
            FATAL("Cannot run application because no primary camera is set!");
            this->Quit();
        }

        if (m_scenesMap.size() < 1)
        {
            FATAL("Cannot run application because no scenes exist!");
            this->Quit();
        }

        while (m_isRunning)
        {
            Graphics::HandleWindowEvents(m_window);
            m_scenesMap[selectedSceneName]->GetEntityManager().Update();
            m_scenesMap[selectedSceneName]->OnUpdate();

            UI::BeginFrame();
            this->OnRenderUI();
            UI::EndFrame();

            Graphics::RendererBegin();
            m_scenesMap[selectedSceneName]->OnRender();
            m_scenesMap[selectedSceneName]->GetEntityManager().DrawEntities();
            Graphics::RendererEnd();
        }
    }

    void Application::Quit()
    {
        m_isRunning = false;
    }

    void Application::AddScene(Scene* scene, const char* name)
    {
        m_scenesMap[name] = scene;
    }

    void Application::RemoveScene(const char* name)
    {
        if (m_scenesMap[name] != NULL)
        {
            m_scenesMap[name]->OnShutdown();
            delete m_scenesMap[name];
            m_scenesMap[name] = NULL;
        }
    }

    void Application::SwitchToScene(const char* name)
    {
        if (m_scenesMap[name] == NULL)
        {
            ERROR("Cannot switch to scene '%s' because it doesn't exist!", name);
            return;
        }

        m_scenesMap[name]->OnCreate();
        selectedSceneName = name;
        INFO("Successfully switched to scene '%s'!", name);
    }

    Scene* Application::GetCurrentScene()
    {
        return m_scenesMap[selectedSceneName];
    }
}
