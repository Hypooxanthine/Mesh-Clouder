#include "States/MainState.h"

#include <ImGui/imgui.h>
#include <ImGui/imgui_internal.h>

#include <iostream>

#include "Data/Mesh.h"
#include "ExternalData/ObjectLoader.h"

MainState::MainState()
    : State(), m_Mesh(nullptr)
{

}

MainState::~MainState()
{

}

void MainState::update()
{
    if (m_ShouldImportMesh)
        importMesh();
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

void MainState::importMesh()
{
    std::cout << "Importing mesh\n";
    try
    {
        m_Mesh = std::make_unique<Mesh>(std::move(ObjectLoader::LoadMesh()));
        m_MeshLoaded = true;
        std::cout << "Mesh loaded.\n";
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    m_ShouldImportMesh = false;
}
