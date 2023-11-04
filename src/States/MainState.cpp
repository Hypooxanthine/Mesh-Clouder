#include "States/MainState.h"

#include <ImGui/imgui.h>
#include <ImGui/imgui_internal.h>

#include <iostream>

#include "Data/Mesh.h"
#include "ExternalData/ObjectLoader.h"

#include "Rendering/VertexArray.h"
#include "Rendering/VertexBuffer.h"
#include "Rendering/VertexBufferLayout.h"
#include "Rendering/IndexBuffer.h"

float verticesData[] =
{
    -0.5f, -0.5f, 0.f,   0.f, 0.f, 0.f,   0.f, 0.f,
     0.5f, -0.5f, 0.f,   0.f, 0.f, 0.f,   1.f, 1.f,
      0.f,  0.5f, 0.f,   0.f, 0.f, 0.f,   1.f, 0.f,
};

unsigned int indicesData[] = 
{
    0, 1, 2,
};

MainState::MainState()
    : State(), m_Mesh(nullptr)
{
    va = std::make_unique<VertexArray>();
    vb = std::make_unique<VertexBuffer>(verticesData, 3 * 8 * sizeof(float));
    layout = std::make_unique<VertexBufferLayout>();
    layout->pushFloat(3);
    layout->pushFloat(3);
    layout->pushFloat(2);
    va->addBuffer(*vb, *layout);
    ib = std::make_unique<IndexBuffer>(indicesData, 3);

    shader = std::make_unique<Shader>();
    shader->loadFromFile("vertex.shader", "fragment.shader");
    
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
}

MainState::~MainState()
{
    glDeleteTextures(1, &texture);
}

void MainState::update()
{
    if (m_ShouldImportMesh)
        importMesh();
}

void MainState::render()
{
    unsigned int fbo;
    GLCall(glGenFramebuffers(1, &fbo));
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

    unsigned int rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo); 
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);  
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;

    m_Renderer.draw(*va, *ib, *shader);
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, 0); 
    glDeleteFramebuffers(1, &fbo);
    glDeleteRenderbuffers(1, &rbo);
}

void MainState::renderImGui()
{
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    window_flags |= ImGuiWindowFlags_NoBackground;
    
    ImGui::Begin("MainWidget", nullptr, window_flags);
        ImGui::PopStyleVar(3);
        ImGuiID dockspace_id = ImGui::GetID("DockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("Options"))
            {
                if (ImGui::MenuItem("Import Mesh", nullptr, false))
                    m_ShouldImportMesh = true;

                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }
    ImGui::End();

    ImGui::Begin("Viewport");
        ImGui::Image((void*)(intptr_t)texture, {800, 600});
    ImGui::End();

    ImGui::Begin("Properties");
    ImGui::End();
}

void MainState::importMesh()
{
    std::cout << "Importing mesh\n";
    try
    {
        m_Mesh = std::make_unique<Mesh>(std::move(ObjectLoader::LoadMesh()));
        m_MeshLoaded = true;
        std::cout << "Mesh loaded.\n";
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    m_ShouldImportMesh = false;
}
