#include "States/MainState.h"

#include <ImGui/imgui.h>
#include <ImGui/imgui_internal.h>

MainState::MainState()
    : State()
{

}

MainState::~MainState()
{

}

void MainState::update()
{

}

void MainState::render()
{

}

void MainState::renderImGui()
{
    ImGui::DockSpaceOverViewport();

    ImGui::Begin("Load a mesh");
    ImGui::End();
    ImGui::Begin("Load a mesh2");
    ImGui::End();
}
