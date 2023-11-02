#include "Data/Mesh.h"

Mesh::Mesh(Mesh&& other)
{
    *this = std::move(other);
}

Mesh& Mesh::operator=(Mesh&& other)
{
    m_Vertices = std::move(other.m_Vertices);
    m_Indices = std::move(other.m_Indices);

    return *this;
}

void Mesh::reserveVertices(unsigned int nb)
{
    m_Vertices.reserve(nb);
}

void Mesh::reserveIndices(unsigned int nb)
{
    m_Indices.reserve(nb);

}
void Mesh::clear()
{
    m_Vertices.clear();
    m_Indices.clear();
}

void Mesh::addVertex(const Vertex& v)
{
    m_Vertices.push_back(v);
}

void Mesh::addVertex(Vertex&& v)
{
    m_Vertices.push_back(std::move(v));
}

void Mesh::defineTriangle(unsigned int a, unsigned int b, unsigned int c)
{
    m_Indices.push_back(a);
    m_Indices.push_back(b);
    m_Indices.push_back(c);
}

size_t Mesh::getVerticesCount() const
{
    return m_Vertices.size();
}

size_t Mesh::getIndicesCount() const
{
    return m_Indices.size();
}

size_t Mesh::getTrianglesCount() const
{
    return getIndicesCount() / 3;
}