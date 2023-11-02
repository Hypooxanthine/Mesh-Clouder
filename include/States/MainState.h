#pragma once

#include "States/State.h"

class MainState : public State
{
public:
    MainState();
    ~MainState();

    virtual void update() override;
    virtual void render() override;
    virtual void renderImGui() override;

private:
    bool m_ShouldImportMesh = false;
};