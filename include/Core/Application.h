#pragma once

#include <GL/glew.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <memory>

class State;

class Application
{
public:
    Application();
    ~Application();

    /**
     * @brief Starts the main loop of the application.
     * 
     */
    void run();

private:
    void initGLFW();
    void initImGui();

    void update();
    void render();
    void renderImGui();

private:
    GLFWwindow* m_Window = nullptr;

    std::unique_ptr<State> m_CurrentState;
};