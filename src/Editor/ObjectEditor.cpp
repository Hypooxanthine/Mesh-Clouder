#include "Editor/ObjectEditor.h"

ObjectEditor::ObjectEditor()
{
    GLCall(glGenTextures(1, &m_Texture));
    loadDefaultCube();
}

ObjectEditor::~ObjectEditor()
{
    GLCall(glDeleteTextures(1, &m_Texture));
}

void ObjectEditor::loadDefaultCube()
{
    Mesh m;

    m.addVertex({{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}); // A 0
    m.addVertex({{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}); // D 1
    m.addVertex({{-0.5f,  0.5f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}); // E 2
    m.addVertex({{-0.5f,  0.5f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}); // H 3
    m.addVertex({{ 0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}); // B 4
    m.addVertex({{ 0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}); // C 5
    m.addVertex({{ 0.5f,  0.5f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}); // F 6
    m.addVertex({{ 0.5f,  0.5f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}); // G 7

    m.defineTriangle(0, 5, 4);
    m.defineTriangle(0, 1, 4);
    m.defineTriangle(0, 4, 2);
    m.defineTriangle(4, 6, 2);
    m.defineTriangle(4, 5, 6);
    m.defineTriangle(5, 7, 6);
    m.defineTriangle(5, 3, 7);
    m.defineTriangle(5, 1, 3);
    m.defineTriangle(0, 2, 3);
    m.defineTriangle(0, 3, 1);
    m.defineTriangle(2, 6, 3);
    m.defineTriangle(6, 7, 3);

    m_RenderMesh = std::make_unique<RenderMesh>(std::move(m));
}

void ObjectEditor::render() const
{
    GLCall(glBindTexture(GL_TEXTURE_2D, m_Texture));

    unsigned int fbo;
    GLCall(glGenFramebuffers(1, &fbo));
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, fbo));

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Texture, 0));

    unsigned int rbo;
    GLCall(glGenRenderbuffers(1, &rbo));
    GLCall(glBindRenderbuffer(GL_RENDERBUFFER, rbo);) 
    GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600); ) 
    GLCall(glBindRenderbuffer(GL_RENDERBUFFER, 0));

    GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo));

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "Frame Buffer not complete." << std::endl;
    
    m_Renderer.draw(*m_RenderMesh);
    
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
    GLCall(glBindRenderbuffer(GL_RENDERBUFFER, 0);) 
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
    GLCall(glDeleteFramebuffers(1, &fbo));
    GLCall(glDeleteRenderbuffers(1, &rbo));
}

void ObjectEditor::setRenderMesh(const RenderMesh& rm)
{
    m_RenderMesh = std::make_unique<RenderMesh>(rm);
}

void ObjectEditor::setRenderMesh(RenderMesh&& rm)
{
    m_RenderMesh = std::make_unique<RenderMesh>(std::move(rm));
}
