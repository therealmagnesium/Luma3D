#pragma once
#include "Core/Base.h"
#include "Core/Scene.h"

#include "Graphics/Framebuffer.h"
#include "Graphics/Window.h"

#include <string>
#include <unordered_map>
#include <vector>

namespace Core
{
    /*
     * [@brief] The specification holds the details of the application.
     * [@field] windowWidth - The width of the window to be created.
     * [@field] windowHeight - The height of the window to be created.
     * [@field] author - Whoever is responsible for creating the application.
     * [@field] name - This will be the name of your application, it will be
                        displayed on the window's titlebar.
     * */
    struct ApplicationSpecification
    {
        u32 windowWidth = 1280;
        u32 windowHeight = 720;
        std::string name = "Luma 3D Application";
        std::string author = "None Specified";
    };

    /*
     * [@brief] A representation of your main application,
     * there should only be one instance of this.
     * The instance of your application can be accesses with the App global variable.
     * */
    class Application
    {
    public:
        /*
         * [@brief] Creates a new application, given the information to create it.
         * [@param] appInfo - The specifications on how to create the application.
         * */
        Application(const ApplicationSpecification& appInfo);

        // [@brief] Frees memory allocated by initializing the application.
        virtual ~Application();

        // [@brief] Returns true if the application is running.
        inline bool IsRunning() const { return m_isRunning; }

        // [@brief] Get the app's specification.
        inline ApplicationSpecification& GetSpecification() { return m_specification; }

        // [@brief] Get the app's framebuffer.
        inline Graphics::Framebuffer& GetFramebuffer() { return m_framebuffer; }

        // [@brief] Get the app's main window.
        inline Graphics::Window& GetWindow() { return m_window; }

        // [@brief] Returns the currently selected scene.
        std::shared_ptr<Scene>& GetActiveScene();

        // [@brief] Sets the given scene to be active.
        void SetActiveScene(const std::shared_ptr<Scene>& scene);

        // [@brief] Start the application, and enter the main game loop.
        void Run();

        // [@brief] Shutdown the application, and exit the main game loop.
        void Quit();

    protected:
        virtual void OnUpdate() {}
        virtual void OnRenderUI() {}

    private:
        bool m_isRunning = false;
        ApplicationSpecification m_specification;
        Graphics::Window m_window;
        Graphics::Framebuffer m_framebuffer;
        std::shared_ptr<Scene> m_activeScene;
    };

    extern Application* App;
}
