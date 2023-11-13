#include "Rendering/Objects/RenderMesh.h"

#include "Data/Vertex.h"
#include "Rendering/VertexBuffer.h"
#include "Rendering/VertexBufferLayout.h"

RenderMesh::RenderMesh()
{
    init();
}

RenderMesh::RenderMesh(const RenderMesh& other)
{
    *this = other;
}

RenderMesh::RenderMesh(RenderMesh&& other)
{
    *this = std::move(other);
}

RenderMesh::RenderMesh(const Mesh& mesh)
    : m_MeshData(mesh)
{
    init();
}

RenderMesh::RenderMesh(Mesh&& mesh)
    : m_MeshData(std::move(mesh))
{
    init();
}

RenderMesh::~RenderMesh()
{
}

RenderMesh& RenderMesh::operator=(const RenderMesh& other)
{
    m_MeshData = other.m_MeshData;
    m_VertexArray = std::make_unique<VertexArray>(*other.m_VertexArray);
    init();
    return *this;
}

RenderMesh& RenderMesh::operator=(RenderMesh&& other)
{
    m_MeshData = std::move(other.m_MeshData);
    m_VertexArray = std::move(std::make_unique<VertexArray>(*other.m_VertexArray));
    init();
    return *this;
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

    m_Shader = std::make_unique<Shader>();
}