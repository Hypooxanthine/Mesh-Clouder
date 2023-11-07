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

    virtual void update() override;
    virtual void render() override;
    virtual void renderImGui() override;

private:
    void importMesh();
    void updateViewportSize(const ImVec2& newSize);
    void handleViewportInputs();

private:
    ObjectEditor m_ObjectEditor;

    bool m_ShouldImportMesh = false;
    bool m_MeshLoaded = false;

    ImVec2 m_PreviousViewportSize;
    ImVec2 m_PreviousMousePos;
    bool m_JustStartedDragging = true;
};