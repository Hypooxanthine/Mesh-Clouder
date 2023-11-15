#include "Rendering/Objects/RenderMesh.h"

#include "Data/Vertex.h"
#include "Rendering/Abstraction/VertexBuffer.h"
#include "Rendering/Abstraction/VertexBufferLayout.h"
#include "Rendering/Renderer.h"

RenderMesh::RenderMesh()
{
    m_Shader = std::make_unique<Shader>();
    m_Shader->loadFromFile("Resources/meshVert.glsl", "Resources/meshFrag.glsl");
}

RenderMesh::~RenderMesh()
{
}

void RenderMesh::render(const Renderer& renderer, const Camera& camera) const
{
    const glm::mat4 MVP = camera.getTransform() * this->getTransform();

    // Updating uniforms
    getShader().bind();
    getShader().setUniformMat4f("u_MVP", MVP);
    getShader().setUniformMat4f("u_M", this->getTransform());

    // Drawing object
    renderer.drawTriangles(getVertexArray(), getIndexBuffer(), getShader());
}

void RenderMesh::setMesh(const Mesh& mesh)
{
    m_MeshData = mesh;
    init();
}

void RenderMesh::setMesh(Mesh&& mesh)
{
    m_MeshData = std::move(mesh);
    init();
}

void RenderMesh::init()
{
    m_VertexArray = std::make_unique<VertexArray>();
    m_VertexBuffer = std::make_unique<VertexBuffer>(m_MeshData.getRawVerticesData(), m_MeshData.getVerticesCount() * sizeof(Vertex));
    m_Layout = std::make_unique<VertexBufferLayout>();
    m_Layout->pushFloat(3);
    m_Layout->pushFloat(3);
    m_Layout->pushFloat(2);
    m_VertexArray->addBuffer(*m_VertexBuffer, *m_Layout);
    m_IndexBuffer = std::make_unique<IndexBuffer>(m_MeshData.getRawIndicesData(), m_MeshData.getIndicesCount());
}