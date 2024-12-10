#pragma once
#include "Core/Base.h"
#include "Core/Scene.h"
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
        ~Application();

        // [@brief] Returns true if the application is running.
        inline bool IsRunning() const { return m_isRunning; }

        // [@brief] Get the app's specification.
        inline ApplicationSpecification& GetSpecification() { return m_specification; }

        // [@brief] Get the app's main window.
        inline Graphics::Window& GetWindow() { return m_window; }

        // [@brief] Returns the currently selected scene.
        Scene* GetCurrentScene();

        // [@brief] Start the application, and enter the main game loop.
        void Run();

        // [@brief] Shutdown the application, and exit the main game loop.
        void Quit();

        // [@brief] Add a scene that can be switched to until it's removed.
        void AddScene(Scene* scene, const char* name);

        // [@brief] Remove a scene from the application's scene map, frees the scene's memory.
        void RemoveScene(const char* name);

        // [@brief] The application will switch to the scene mapped with the given name.
        void SwitchToScene(const char* name);

    protected:
        virtual void OnRenderUI() {}

    private:
        bool m_isRunning = false;
        ApplicationSpecification m_specification;
        std::unordered_map<std::string, Scene*> m_scenesMap;
        Graphics::Window m_window;
    };

    extern Application* App;
}
