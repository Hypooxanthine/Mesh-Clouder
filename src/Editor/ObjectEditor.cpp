#include "Editor/ObjectEditor.h"

#include <glm/gtc/matrix_transform.hpp>

#include "ExternalData/ObjectLoader.h"
#include "Rendering/Objects/MeshGenerator.h"
#include "Math/Math.h"

ObjectEditor::ObjectEditor()
{
    m_Camera.setIsUsingOrbiting(true);

    loadDefaultCube();
    
    m_BrushMesh = std::make_unique<RenderMesh>(MeshGenerator::GenCircle(64));
    m_BrushMesh->getShader().loadFromFile("Resources/brushVert.glsl", "Resources/brushFrag.glsl");

    m_CoordinateSystem = std::make_unique<RenderGrid>(glm::vec2{50.f, 50.f}, glm::vec2{1.f, 1.f});

    m_Renderer.setViewport({0, 0}, {800, 600});

    updateRenderObjectsMatrices();
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
    updateRenderObjectsMatrices();
}

void ObjectEditor::setRenderMesh(RenderMesh&& rm)
{
    m_RenderMesh = std::make_unique<RenderMesh>(std::move(rm));
    m_RenderMesh->getShader().loadFromFile("Resources/meshVert.glsl", "Resources/meshFrag.glsl");
    updateRenderObjectsMatrices();
}

void ObjectEditor::onWindowAspectRatioChanged(float x, float y)
{
    m_RenderTargetSize = { x, y };
    m_Renderer.setViewportSize({x, y});
    m_Camera.setAspectRatio(x / y);
    updateRenderObjectsMatrices();
}

void ObjectEditor::onUserDrag(const glm::vec2& drag)
{
    m_Camera.setViewAzimuth(m_Camera.getViewAzimuth() - drag.x * m_OrbitSpeed);
    m_Camera.setViewElevation(m_Camera.getViewElevation() + drag.y * m_OrbitSpeed);
    updateRenderObjectsMatrices();
}

void ObjectEditor::onUserZoom(float value)
{
    m_Camera.setViewDistance(m_Camera.getViewDistance() - value * m_ZoomSpeed);
    updateRenderObjectsMatrices();
}

void ObjectEditor::onMouseMoved(float x, float y)
{
    if(!(x >= 0 && y >= 0 && x < m_RenderTargetSize.x && y < m_RenderTargetSize.y))
    {
        m_ShouldRenderBrush = false;
        return;
    }

    Ray ray = Math::RayUnderCursor(m_Camera.getTranslation(), m_Camera.getTransform(), glm::vec2(x, y), m_RenderTargetSize);

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

void ObjectEditor::updateRenderObjectsMatrices()
{
    if (m_RenderMesh)
        updateRenderObjectMatrices(*m_RenderMesh);

    if (m_BrushMesh)
        updateRenderObjectMatrices(*m_BrushMesh);

    if (m_CoordinateSystem)
        updateRenderObjectMatrices(*m_CoordinateSystem);
}

void ObjectEditor::updateRenderObjectMatrices(RenderObject& obj)
{
    glm::mat4 MV = m_Camera.getViewTransform() * obj.getTransform();
    glm::mat4 MVP = m_Camera.getTransform() * obj.getTransform();

    obj.getShader().bind();
    obj.getShader().setUniformMat4f("u_MVP", MVP);
    obj.getShader().setUniformMat4f("u_MV", MV);
    obj.getShader().setUniformMat4f("u_P", obj.getTransform());
}