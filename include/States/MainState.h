#pragma once

#include <ImGui/imgui.h>

#include "States/State.h"

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
    void importMesh();
    void updateViewportSize(const ImVec2& newSize);
    void handleViewportInputs();

private:
    ObjectEditor m_ObjectEditor;

    /* ImGui related vars */
    bool m_ShouldImportMesh = false;
    bool m_RealTimePointCloudGeneration = true;
    int m_SelectedView = 0;
    float m_PointSize = 0.05f;

    ImVec2 m_PreviousViewportSize;
    ImVec2 m_PreviousMousePos;
    bool m_JustStartedDragging = true;
};