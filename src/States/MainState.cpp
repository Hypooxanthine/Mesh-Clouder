#include "States/MainState.h"

#include <ImGui/imgui.h>

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
    ImGui::ShowDemoWindow();
}