#include "Editor/ObjectEditor.h"

#include <glm/gtc/matrix_transform.hpp>

#include "ExternalData/ObjectLoader.h"
#include "Rendering/Objects/MeshGenerator.h"
#include "Math/Math.h"

ObjectEditor::ObjectEditor()
{
    m_RenderMesh = std::make_unique<RenderMesh>();
    m_RenderPointCloud = std::make_unique<RenderPointCloud>();
    m_BrushMesh = std::make_unique<RenderMesh>();
    m_BrushMesh->setMesh(MeshGenerator::GenCircle(64));
    m_BrushMesh->getShader().loadFromFile("Resources/brushVert.glsl", "Resources/brushFrag.glsl");
    m_CoordinateSystem = std::make_unique<RenderGrid>(glm::vec2{50.f, 50.f}, glm::vec2{1.f, 1.f});
    m_Camera.setIsUsingOrbiting(true);

    loadDefaultCube();

    m_Renderer.setViewport({0, 0}, {800, 600});
}

ObjectEditor::~ObjectEditor()
{
}

void ObjectEditor::loadDefaultCube()
{
    try
    {
        setRenderMesh(ObjectLoader::LoadMesh("Resources/defaultCube.obj"));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        setRenderMesh(Mesh());
    }
}

void ObjectEditor::update()
{
    if(m_RealTimeProcessing && m_ShouldProcess)
    {
        processPointCloud();
        m_ShouldProcess = false;
    }
}

void ObjectEditor::render()
{
    m_Renderer.beginScene();

    if(m_ShouldRenderMesh)
        m_Renderer.draw(*m_RenderMesh, m_Camera);
    if(m_ShouldRenderPointCloud)
        m_Renderer.draw(*m_RenderPointCloud, m_Camera);
    if (false && m_ShouldRenderBrush) // Brush system not implemented yet
        m_Renderer.draw(*m_BrushMesh, m_Camera);
    m_Renderer.draw(*m_CoordinateSystem, m_Camera);

    m_Renderer.endScene();
}


void ObjectEditor::setRenderMesh(const Mesh& m)
{
    m_RenderMesh->setMesh(m);
    processPointCloud();
}

void ObjectEditor::setRenderMesh(Mesh&& m)
{
    m_RenderMesh->setMesh(std::move(m));
    processPointCloud();
}

void ObjectEditor::setShouldRenderMesh(bool val)
{
    m_ShouldRenderMesh = val;
}

void ObjectEditor::setShouldRenderPointCloud(bool val)
{
    m_ShouldRenderPointCloud = val;
}

void ObjectEditor::setPointSize(float size)
{
    m_RenderPointCloud->setPointSize(size);
}

void ObjectEditor::setRealTimeProcessing(float val)
{
    m_RealTimeProcessing = val;
}

void ObjectEditor::setPointCloudDensity(float val)
{
    m_Processor.setDensity(val);
    m_ShouldProcess = true;
}

void ObjectEditor::setPointCloudMinDisturb(const glm::vec3& min)
{
    m_Processor.setMinDisturb(min);
    m_ShouldProcess = true;
}

void ObjectEditor::addPointCloudMinDisturb(const glm::vec3& minDelta)
{
    setPointCloudMinDisturb(m_Processor.getMinDisturb() + minDelta);
}

void ObjectEditor::setPointCloudMaxDisturb(const glm::vec3& max)
{
    m_Processor.setMaxDisturb(max);
    m_ShouldProcess = true;
}

void ObjectEditor::addPointCloudMaxDisturb(const glm::vec3& maxDelta)
{
    setPointCloudMaxDisturb(m_Processor.getMaxDistrub() + maxDelta);
}

void ObjectEditor::setSeed(uint32_t seed)
{
    m_Processor.setSeed(seed);
    m_ShouldProcess = true;
}

void ObjectEditor::processPointCloud()
{
    m_RenderPointCloud->setPointCloud(m_Processor.process(m_RenderMesh->getMeshData()));
}

void ObjectEditor::onWindowAspectRatioChanged(float x, float y)
{
    m_RenderTargetSize = { x, y };
    m_Renderer.setViewportSize({x, y});
    m_Camera.setAspectRatio(x / y);
}

void ObjectEditor::onUserDrag(const glm::vec2& drag)
{
    m_Camera.setViewAzimuth(m_Camera.getViewAzimuth() - drag.x * m_OrbitSpeed);
    m_Camera.setViewElevation(m_Camera.getViewElevation() + drag.y * m_OrbitSpeed);
}

void ObjectEditor::onUserZoom(float value)
{
    if(value < 0.f)
        m_Camera.setViewDistance(m_Camera.getViewDistance() * (1.f - value * m_ZoomSpeed));
    else
        m_Camera.setViewDistance(m_Camera.getViewDistance() / (1.f + value * m_ZoomSpeed));
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
    m_BrushMesh->setTranslation(res.position + res.normal * 0.0001f * m_Camera.getViewDistance());
    m_BrushMesh->setRotation(Math::AlignVectors(m_BrushMesh->getMeshData().getVertices()[0].normal, res.normal));
}

const PointCloud& ObjectEditor::getPointCloudData() const
{
    return m_RenderPointCloud->getPointCloud();
}