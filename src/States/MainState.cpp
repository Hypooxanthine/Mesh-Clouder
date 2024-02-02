#include "States/MainState.h"

#include <ImGui/imgui_internal.h>

#include <iostream>

#include "ExternalData/ObjectLoader.h"
#include "Data/Mesh.h"

MainState::MainState()
    : State()
{
    setProject(Project());
}

MainState::~MainState()
{
}

void MainState::update()
{
    if (m_ShouldImportMesh)
        importMesh();
    
    if (m_ShouldExportPointCloud)
        exportPointCloud();

    if (m_ShouldLoadProject)
        loadProject();

    if (m_ShouldSaveProject)
        saveProject();

    if (m_ShouldSaveProjectAs)
        saveProjectAs();

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
                ImGui::MenuItem("Load project", nullptr, &m_ShouldLoadProject);
                ImGui::MenuItem("Save project", nullptr, &m_ShouldSaveProject);
                ImGui::MenuItem("Save project as...", nullptr, &m_ShouldSaveProjectAs);
                ImGui::MenuItem("Import mesh", nullptr, &m_ShouldImportMesh);
                ImGui::MenuItem("Export point cloud", nullptr, &m_ShouldExportPointCloud);

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
        if(ImGui::Combo("##ViewComboLabel", &m_SelectedView, viewItems, IM_ARRAYSIZE(viewItems)))
        {
            m_ObjectEditor.setShouldRenderMesh(m_SelectedView == 0 || m_SelectedView == 2);
            m_ObjectEditor.setShouldRenderPointCloud(m_SelectedView == 1 || m_SelectedView == 2);
        }
        if(ImGui::Checkbox("Real time point cloud processing", &m_Project.getSettings().realTimePointCloudGeneration))
        {
            m_ObjectEditor.setRealTimeProcessing(m_Project.getSettings().realTimePointCloudGeneration);
        }
        ImGui::Text("Point size:");
        ImGui::SameLine();
        if(ImGui::SliderFloat("##PointSizeSlider", &m_Project.getSettings().pointSize, 0.0001f, 0.1f, "%.4f"))
        {
            m_ObjectEditor.setPointSize(m_Project.getSettings().pointSize);
        }
        ImGui::Text("Density:");
        ImGui::SameLine();
        if(ImGui::SliderFloat("##DensitySlider", &m_Project.getSettings().density, 0.f, 20.f, "%.1f"))
        {
            m_ObjectEditor.setPointCloudDensity(m_Project.getSettings().density);
        }
        ImGui::Text("Min disturb:");
        ImGui::SameLine();
        if(ImGui::SliderFloat3("##MinDisturbSlider", &m_Project.getSettings().minDisturb.x, -.05f, .05f, "%.3f"))
        {
            m_ObjectEditor.setPointCloudMinDisturb(m_Project.getSettings().minDisturb);
        }
        ImGui::Text("Max disturb:");
        ImGui::SameLine();
        if(ImGui::SliderFloat3("##MaxDisturbSlider", &m_Project.getSettings().maxDisturb.x, -.05f, .05f, "%.3f"))
        {
            m_ObjectEditor.setPointCloudMaxDisturb(m_Project.getSettings().maxDisturb);
        }
        ImGui::Text("Seed:");
        ImGui::SameLine();
        if(ImGui::SliderInt("##SeedSlider", &m_Project.getSettings().seed, 0, 20))
        {
            m_ObjectEditor.setSeed((uint32_t)m_Project.getSettings().seed);
        }
    ImGui::End();

    ImGui::Begin("Actions");
        if(m_Project.getSettings().realTimePointCloudGeneration) ImGui::BeginDisabled();
            if(ImGui::Button("Process point cloud"))
            {
                m_ObjectEditor.processPointCloud();
            }
        if(m_Project.getSettings().realTimePointCloudGeneration) ImGui::EndDisabled();
    ImGui::End();
}

void MainState::setProject(const Project& project)
{
    m_Project = project;

    updateAllEditorSettings();
}

void MainState::loadProject()
{
    std::cout << "Loading project.\n";
    try
    {
        Project p = ObjectLoader::LoadProject();
        setProject(p);
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    m_ShouldLoadProject = false;
}

void MainState::saveProject()
{
    std::cout << "Saving project.\n";

    if (!m_Project.hasDefinedFilePath())
    {
        saveProjectAs();
        m_ShouldSaveProject = false;
        return;
    }

    try
    {
        ObjectLoader::SaveProject(m_Project);
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    m_ShouldSaveProject = false;
}

void MainState::saveProjectAs()
{
    std::cout << "Saving project as..\n";

    try
    {
        ObjectLoader::SaveProjectAs(m_Project);
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    m_ShouldSaveProjectAs = false;
}

void MainState::updateAllEditorSettings()
{
    m_ObjectEditor.setRealTimeProcessing(m_Project.getSettings().realTimePointCloudGeneration);
    m_ObjectEditor.setPointSize(m_Project.getSettings().pointSize);
    m_ObjectEditor.setPointCloudDensity(m_Project.getSettings().density);
    m_ObjectEditor.setPointCloudMinDisturb(m_Project.getSettings().minDisturb);
    m_ObjectEditor.setPointCloudMaxDisturb(m_Project.getSettings().maxDisturb);
    m_ObjectEditor.setSeed((uint32_t)m_Project.getSettings().seed);
}

void MainState::importMesh()
{
    std::cout << "Importing mesh.\n";
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

void MainState::exportPointCloud()
{
    std::cout << "Exporting point cloud.\n";
    try
    {
        const PointCloud& pc = m_ObjectEditor.getPointCloudData();

        ObjectLoader::SavePointCloud(pc);
        std::cout << "Point cloud saved.\n";
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    m_ShouldExportPointCloud = false;
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