#include "States/MainState.h"

#include <ImGui/imgui_internal.h>

#include <iostream>

#include "ExternalData/ObjectLoader.h"
#include "Data/Mesh.h"

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
        importMesh();
    
    m_ObjectEditor.update();
}

void MainState::render()
{
    m_ObjectEditor.render();
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
            if (ImGui::BeginMenu("File"))
            {
                ImGui::MenuItem("Import Mesh", nullptr, &m_ShouldImportMesh);

                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }
    ImGui::End();

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::Begin("Viewport");
        ImGui::BeginChild("RenderViewport");
            auto vpSize = ImGui::GetWindowSize();
            updateViewportSize(vpSize);
            // Inverting V from UV because OpenGL textures are flipped vertically
            ImGui::Image((void*)(intptr_t)m_ObjectEditor.getDrawnSceneTextureIndex(), vpSize, ImVec2(0, 1), ImVec2(1, 0));

            handleViewportInputs();
        ImGui::EndChild();
    ImGui::End();
    ImGui::PopStyleVar(2);

    ImGui::Begin("Settings");
        ImGui::Text("View:");
        ImGui::SameLine();
        const char* viewItems[] = { "Mesh", "Point cloud", "Both" };
        ImGui::Combo("##ViewComboLabel", &m_SelectedView, viewItems, IM_ARRAYSIZE(viewItems));
        ImGui::Checkbox("Real time point cloud processing", &m_RealTimePointCloudGeneration);
    ImGui::End();

    ImGui::Begin("Actions");
        if(m_RealTimePointCloudGeneration) ImGui::BeginDisabled();
            ImGui::Button("Process point cloud");
        if(m_RealTimePointCloudGeneration) ImGui::EndDisabled();
    ImGui::End();
}

void MainState::importMesh()
{
    std::cout << "Importing mesh\n";
    try
    {
        Mesh mesh = ObjectLoader::LoadMesh();
        m_ObjectEditor.setRenderMesh(std::move(mesh));
        std::cout << "Mesh loaded.\n";
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    m_ShouldImportMesh = false;
}

void MainState::updateViewportSize(const ImVec2& newSize)
{
    if (newSize.x == m_PreviousViewportSize.x && newSize.y == m_PreviousViewportSize.y)
        return;
    
    m_ObjectEditor.onWindowAspectRatioChanged(newSize.x, newSize.y);
    m_PreviousViewportSize = newSize;
}

void MainState::handleViewportInputs()
{
    auto mousePos = ImGui::GetMousePos();

    if (ImGui::IsItemHovered())
    {
        if (ImGui::IsMouseDragging(2) && (mousePos.x != m_PreviousMousePos.x || mousePos.y != m_PreviousMousePos.y))
        {
            if(m_JustStartedDragging)
            {
                m_JustStartedDragging = false;
            }
            else
            {
                glm::vec2 dragging = {mousePos.x - m_PreviousMousePos.x, mousePos.y - m_PreviousMousePos.y};
                m_ObjectEditor.onUserDrag(dragging);
            }
        }

        if (ImGui::IsMouseReleased(2))
        {
            m_JustStartedDragging = true;
        }

        ImGuiIO& io = ImGui::GetIO();
        if (io.MouseWheel != 0.f)
            m_ObjectEditor.onUserZoom(io.MouseWheel);
    }
    else
    {
        m_JustStartedDragging = true;
    }

    ImVec2 viewportPos = ImGui::GetItemRectMin();

    if(mousePos.x != m_PreviousMousePos.x || mousePos.y != m_PreviousMousePos.y)
        m_ObjectEditor.onMouseMoved(mousePos.x - viewportPos.x, mousePos.y - viewportPos.y);

    m_PreviousMousePos = mousePos;
}