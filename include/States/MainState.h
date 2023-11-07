#pragma once

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

private:
    ObjectEditor m_ObjectEditor;

    bool m_ShouldImportMesh = false;
    bool m_MeshLoaded = false;
};