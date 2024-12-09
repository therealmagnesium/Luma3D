#include "UI/UI.h"

#include "Core/Application.h"
#include "Core/Base.h"
#include "Core/Log.h"

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>

namespace UI
{
    void SetupContext()
    {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

        Graphics::Window& window = Core::App->GetWindow();
        ImGui_ImplSDL2_InitForOpenGL(window.handle, window.context);
        ImGui_ImplOpenGL3_Init("#version 450");

        INFO("Succesfully initialized the UI context!");
    }

    void ShutdownContext()
    {
        INFO("Shutting down UI context...");
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    }

    void ProcessEvent(SDL_Event* event)
    {
        ImGui_ImplSDL2_ProcessEvent(event);
    }

    void BeginFrame()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
    }

    void EndFrame()
    {
        ImGui::Render();
    }

    void RenderFrame()
    {
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}
