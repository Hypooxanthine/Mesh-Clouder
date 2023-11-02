#include "States/MainState.h"

#include <ImGui/imgui.h>
#include <ImGui/imgui_internal.h>

#include <iostream>

MainState::MainState()
    : State()
{

}

MainState::~MainState()
{

}

void MainState::update()
{
    if (m_ShouldImportMesh)
    {
        std::cout << "Importing mesh\n";
        m_ShouldImportMesh = false;
    }
}

void MainState::render()
{

}

void MainState::renderImGui()
{
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    window_flags |= ImGuiWindowFlags_NoBackground;
    
    ImGui::Begin("MainWidget", nullptr, window_flags);
        ImGui::PopStyleVar(3);
        ImGuiID dockspace_id = ImGui::GetID("DockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("Options"))
            {
                if (ImGui::MenuItem("Import Mesh", nullptr, false))
                    m_ShouldImportMesh = true;

                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }
    ImGui::End();

    ImGui::Begin("Viewport");
    ImGui::End();

    ImGui::Begin("Properties");
    ImGui::End();
    //ImGui::ShowDemoWindow();
}
