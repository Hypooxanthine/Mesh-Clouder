#include "Rendering/Objects/RenderPointCloud.h"

#include "Data/Vertex.h"
#include "Rendering/Abstraction/VertexBuffer.h"
#include "Rendering/Abstraction/VertexBufferLayout.h"
#include "Rendering/Renderer.h"

RenderPointCloud::RenderPointCloud()
{
    m_Shader = std::make_unique<Shader>();
    m_Shader->loadFromFile("Resources/pointCloudVert.glsl", "Resources/pointCloudFrag.glsl", "Resources/pointCloudGeom.glsl");
}

RenderPointCloud::~RenderPointCloud()
{}

void RenderPointCloud::render(const Renderer& renderer, const Camera& camera) const
{
    const glm::mat4 MVP = camera.getTransform() * this->getTransform();

    // Updating uniforms
    getShader().bind();
    getShader().setUniformMat4f("u_MVP", MVP);
    
    renderer.drawPoints(getVertexArray(), getIndexBuffer(), getShader());
}

void RenderPointCloud::setPointCloud(const PointCloud& pc)
{
    m_PointCloudData = pc;
    init();
}

void RenderPointCloud::setPointCloud(PointCloud&& pc)
{
    m_PointCloudData = std::move(pc);
    init();
}

float RenderPointCloud::getCircleRadius() const
{
    return m_CircleRadius;
}

void RenderPointCloud::setCircleRadius(float r)
{
    m_CircleRadius = r;
}


void RenderPointCloud::init()
{
    m_VertexArray = std::make_unique<VertexArray>();
    m_VertexBuffer = std::make_unique<VertexBuffer>(m_PointCloudData.getRawPointsData(), m_PointCloudData.getPointsCount() * sizeof(PointCloud::Element));
    m_Layout = std::make_unique<VertexBufferLayout>();
    m_Layout->pushFloat(3);
    m_Layout->pushFloat(3);
    m_VertexArray->addBuffer(*m_VertexBuffer, *m_Layout);
    m_IndexBuffer = std::make_unique<IndexBuffer>(m_PointCloudData.getRawIndicesData(), m_PointCloudData.getIndicesCount());
}

