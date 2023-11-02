#pragma once

#include <GL/glew.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

class Application
{
public:
    Application();
    ~Application();

    void run();

private:
    void initGLFW();
    void initImGui();

private:
    GLFWwindow* m_Window = nullptr;
};