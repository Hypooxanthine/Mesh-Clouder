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
    auto cameraUp = camera.getUpVector();
    auto cameraRight = camera.getRightVector();

    // Updating uniforms
    getShader().bind();
    getShader().setUniformMat4f("u_MVP", MVP);
    getShader().setUniformMat4f("u_VP", camera.getTransform());
    getShader().setUniform1f("u_PointSize", m_PointSize);
    getShader().setUniform3f("u_CameraRight", cameraRight);
    getShader().setUniform3f("u_CameraUp", cameraUp);
    
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

const PointCloud& RenderPointCloud::getPointCloud() const
{
    return m_PointCloudData;
}

float RenderPointCloud::getPointSize() const
{
    return m_PointSize;
}

void RenderPointCloud::setPointSize(float s)
{
    m_PointSize = s;
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

