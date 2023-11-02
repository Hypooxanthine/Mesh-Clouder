#pragma once

#include "States/State.h"

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
    bool m_ShouldImportMesh = false;

    bool m_MeshLoaded = false;
    std::unique_ptr<Mesh> m_Mesh;
};