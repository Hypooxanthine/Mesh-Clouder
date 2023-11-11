#include "Editor/ObjectEditor.h"

#include <glm/gtc/matrix_transform.hpp>

#include "ExternalData/ObjectLoader.h"
#include "Rendering/Objects/MeshGenerator.h"
#include "Math/Math.h"

ObjectEditor::ObjectEditor()
{
    GLCall(glGenTextures(1, &m_Texture));
    
    loadDefaultCube();
    m_BrushMesh = std::make_unique<RenderMesh>(MeshGenerator::GenCircle(64));
    m_BrushMesh->getShader().loadFromFile("Resources/brushVert.glsl", "Resources/brushFrag.glsl");

    computeProjection();
    computeView();
    computeMVP();

    GLCall(glClearColor(0.1f, 0.1f, 0.1f, 1.f));
}

ObjectEditor::~ObjectEditor()
{
    GLCall(glDeleteTextures(1, &m_Texture));
}

void ObjectEditor::loadDefaultCube()
{
    try
    {
        setRenderMesh(RenderMesh(ObjectLoader::LoadMesh("Resources/defaultCube.obj")));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        setRenderMesh(RenderMesh(Mesh()));
    }
}

void ObjectEditor::update()
{
    
}

void ObjectEditor::render() const
{
    GLCall(glEnable(GL_DEPTH_TEST));

    GLCall(glViewport(0, 0, m_RenderTargetSize.x, m_RenderTargetSize.y));

    GLCall(glBindTexture(GL_TEXTURE_2D, m_Texture));

    unsigned int fbo;
    GLCall(glGenFramebuffers(1, &fbo));
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, fbo));

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_RenderTargetSize.x, m_RenderTargetSize.y, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Texture, 0));

    unsigned int rbo;
    GLCall(glGenRenderbuffers(1, &rbo));
    GLCall(glBindRenderbuffer(GL_RENDERBUFFER, rbo));
    GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_RenderTargetSize.x, m_RenderTargetSize.y));
    GLCall(glBindRenderbuffer(GL_RENDERBUFFER, 0));

    GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo));

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "Frame Buffer not complete." << std::endl;

    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    m_Renderer.draw(*m_RenderMesh);
    if (m_ShouldRenderBrush)
        m_Renderer.draw(*m_BrushMesh);

    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
    GLCall(glBindRenderbuffer(GL_RENDERBUFFER, 0));
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
    GLCall(glDeleteFramebuffers(1, &fbo));
    GLCall(glDeleteRenderbuffers(1, &rbo));

    GLCall(glDisable(GL_DEPTH_TEST));
}


void ObjectEditor::setRenderMesh(const RenderMesh& rm)
{
    m_RenderMesh = std::make_unique<RenderMesh>(rm);
    computeMVP();
}

void ObjectEditor::setRenderMesh(RenderMesh&& rm)
{
    m_RenderMesh = std::make_unique<RenderMesh>(std::move(rm));
    m_RenderMesh->getShader().loadFromFile("Resources/meshVert.glsl", "Resources/meshFrag.glsl");
    computeMVP();
}

void ObjectEditor::onWindowAspectRatioChanged(float x, float y)
{
    m_RenderTargetSize = { x, y };
    m_AspectRatio = x / y;
    computeProjection();
    computeMVP();
}

void ObjectEditor::onUserDrag(const glm::vec2& drag)
{
    m_ViewAzimuth -= drag.x * m_OrbitSpeed;
    m_ViewElevation -= drag.y * m_OrbitSpeed;

    const float epsilon = 0.001f;

    while (m_ViewAzimuth > 360.f) m_ViewAzimuth -= 360.f;
    if (m_ViewElevation > 180.f) m_ViewElevation = 180.f - epsilon;
    else if (m_ViewElevation < 0.f) m_ViewElevation = epsilon;

    computeView();
    computeMVP();
}

void ObjectEditor::onUserZoom(float value)
{
    m_ViewDistance -= value * m_ZoomSpeed;
    computeView();
    computeMVP();
}

void ObjectEditor::onMouseMoved(float x, float y)
{
    //std::cout << "Viewport : " << m_RenderTargetSize.x << ", " << m_RenderTargetSize.y << std::endl;
    //std::cout << "Mouse : " << x << ", " << y << std::endl;

    if(!(x >= 0 && y >= 0 && x < m_RenderTargetSize.x && y < m_RenderTargetSize.y))
    {
        m_ShouldRenderBrush = false;
        return;
    }

    Ray ray = Math::RayUnderCursor(m_CameraPos, m_VPMatrix, glm::vec2(x, y), m_RenderTargetSize);

    HitResult res = Math::RayCastWithMesh(ray, m_RenderMesh->getMeshData());

    if(!res.hasHit)
    {
        m_ShouldRenderBrush = false;
        return;
    }

    m_ShouldRenderBrush = true;
    m_BrushMesh->setTranslation(res.position + res.normal * 0.001f);
    m_BrushMesh->setRotation(Math::AlignVectors(m_BrushMesh->getMeshData().getVertices()[0].normal, res.normal));

    updateRenderObjectMatrices(*m_BrushMesh);
}

void ObjectEditor::computeView()
{
    m_CameraPos.x = m_ViewDistance * sin(glm::radians(m_ViewElevation)) * sin(glm::radians(m_ViewAzimuth));
    m_CameraPos.y = m_ViewDistance * cos(glm::radians(m_ViewElevation));
    m_CameraPos.z = m_ViewDistance * sin(glm::radians(m_ViewElevation)) * cos(glm::radians(m_ViewAzimuth));
    
    //m_ViewMatrix = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -20.f));
    m_ViewMatrix = glm::lookAt(m_CameraPos, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
}

void ObjectEditor::computeProjection()
{
    m_ProjMatrix = glm::perspective(m_Fov, m_AspectRatio, m_NearClip, m_FarClip);
}

void ObjectEditor::computeMVP()
{
    m_VPMatrix = m_ProjMatrix * m_ViewMatrix;

    if (m_RenderMesh)
        updateRenderObjectMatrices(*m_RenderMesh);

    if (m_BrushMesh)
        updateRenderObjectMatrices(*m_BrushMesh);
}

void ObjectEditor::updateRenderObjectMatrices(RenderObject& obj)
{
    glm::mat4 MV = m_ViewMatrix * obj.getTransform();
    glm::mat4 MVP = m_VPMatrix * obj.getTransform();

    obj.getShader().bind();
    obj.getShader().setUniformMat4f("u_MVP", MVP);
    obj.getShader().setUniformMat4f("u_MV", MV);
}