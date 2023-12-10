#include "Core/Application.h"

#include <cstdlib>
#include <thread>
#include <chrono>

#include <ImGui/imgui.h>
#include <ImGui/impl/imgui_impl_glfw.h>
#include <ImGui/impl/imgui_impl_opengl3.h>

#include "States/State.h"
#include "States/MainState.h"

Application::Application()
{
    initGLFW();

    if (glewInit() != GLEW_OK)
    {
        glfwTerminate();
        std::cerr << "Failed to initialize GLEW" << std::endl;
        exit(EXIT_FAILURE);
    }

    initImGui();

    m_CurrentState = std::make_unique<MainState>();
}

Application::~Application()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(m_Window);
 
    glfwTerminate();
}

void Application::initGLFW()
{
    if (!glfwInit())
        std::exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    
    m_Window = glfwCreateWindow(1000, 800, "Mesh Clouder", NULL, NULL);

    if (!m_Window)
    {
        glfwTerminate();
        std::exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(m_Window);
}

void Application::initImGui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch
    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    io.FontGlobalScale = 1.3f;

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(m_Window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();
}

void Application::run()
{
    const double minFrameTime = 1.0 / 144.0;

    while (!glfwWindowShouldClose(m_Window))
    {
        double startTime = glfwGetTime();
        
        if (m_CurrentState->isPendingKilled())
            m_CurrentState = std::move(m_CurrentState->getNextState());

        glfwPollEvents();

        update();
        render();
        renderImGui();

        glfwSwapBuffers(m_Window);

        double elapsedTime = glfwGetTime() - startTime;
        if (elapsedTime < minFrameTime)
        {
            int sleepTime = static_cast<int>((minFrameTime - elapsedTime) * 1000);
            std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
        }
    }


}

void Application::update()
{
    m_CurrentState->update();
}

void Application::render()
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
    m_CurrentState->render();
}

void Application::renderImGui()
{
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    m_CurrentState->renderImGui();

    ImGui::Render();
    ImGui::EndFrame();
    
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
