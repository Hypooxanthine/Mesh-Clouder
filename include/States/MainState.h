#pragma once

#include <ImGui/imgui.h>

#include "States/State.h"

#include "Data/Project.h"
#include "Editor/ObjectEditor.h"

class Mesh;

class MainState : public State
{
public:
    MainState();
    ~MainState();

    /**
     * @brief Deals with data each frame.
     * 
     */
    virtual void update() override;

    /**
     * @brief Renders things on screen each frame.
     * 
     */
    virtual void render() override;

    /**
     * @brief Renders ImGui widgets each frame.
     * 
     */
    virtual void renderImGui() override;

private:
    void setProject(const Project& project);

    void loadProject();
    void saveProject();
    void saveProjectAs();

    void updateAllEditorSettings();

    void importMesh();
    void exportPointCloud();
    void updateViewportSize(const ImVec2& newSize);
    void handleViewportInputs();

private:
    Project m_Project;
    ObjectEditor m_ObjectEditor;

    /* ImGui related vars */
    bool m_ShouldLoadProject = false;
    bool m_ShouldSaveProject = false;
    bool m_ShouldSaveProjectAs = false;
    bool m_ShouldImportMesh = false;
    bool m_ShouldExportPointCloud = false;
    int m_SelectedView = 0;

    ImVec2 m_PreviousViewportSize;
    ImVec2 m_PreviousMousePos;
    bool m_JustStartedDragging = true;
};