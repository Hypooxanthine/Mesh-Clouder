#include "Editor/ObjectEditor.h"

#include <glm/gtc/matrix_transform.hpp>

#include "ExternalData/ObjectLoader.h"
#include "Rendering/Objects/MeshGenerator.h"
#include "Math/Math.h"

ObjectEditor::ObjectEditor()
{    
    loadDefaultCube();
    
    m_BrushMesh = std::make_unique<RenderMesh>(MeshGenerator::GenCircle(64));
    m_BrushMesh->getShader().loadFromFile("Resources/brushVert.glsl", "Resources/brushFrag.glsl");

    m_CoordinateSystem = std::make_unique<RenderGrid>(glm::vec2{50.f, 50.f}, glm::vec2{1.f, 1.f});

    m_Renderer.setViewport({0, 0}, {800, 600});

    computeProjection();
    computeView();
    computeMVP();
}

ObjectEditor::~ObjectEditor()
{
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

void ObjectEditor::render()
{
    m_Renderer.beginScene();

    m_Renderer.draw(*m_RenderMesh);
    if (m_ShouldRenderBrush)
        m_Renderer.draw(*m_BrushMesh);
    m_Renderer.draw(*m_CoordinateSystem);

    m_Renderer.endScene();
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
    m_Renderer.setViewportSize({x, y});
    computeProjection();
    computeMVP();
}

void ObjectEditor::onUserDrag(const glm::vec2& drag)
{
    m_ViewAzimuth -= drag.x * m_OrbitSpeed;
    m_ViewElevation += drag.y * m_OrbitSpeed;

    const float epsilon = 0.001f;

    while (m_ViewAzimuth > 360.f) m_ViewAzimuth -= 360.f;
    while (m_ViewAzimuth < 0.f) m_ViewAzimuth += 360.f;
    m_ViewElevation = glm::clamp(m_ViewElevation, epsilon, 180.f - epsilon);

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
    m_CameraPos.y = -m_ViewDistance * cos(glm::radians(m_ViewElevation));
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

    if (m_CoordinateSystem)
        updateRenderObjectMatrices(*m_CoordinateSystem);
}

void ObjectEditor::updateRenderObjectMatrices(RenderObject& obj)
{
    glm::mat4 MV = m_ViewMatrix * obj.getTransform();
    glm::mat4 MVP = m_VPMatrix * obj.getTransform();

    obj.getShader().bind();
    obj.getShader().setUniformMat4f("u_MVP", MVP);
    obj.getShader().setUniformMat4f("u_MV", MV);
    obj.getShader().setUniformMat4f("u_P", obj.getTransform());
}