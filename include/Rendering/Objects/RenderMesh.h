#pragma once

#include "RenderObject.h"
#include "Data/Mesh.h"

class RenderMesh : public RenderObject
{
public:
    RenderMesh(const RenderMesh& other);
    RenderMesh(RenderMesh&& other);
    RenderMesh(const Mesh& mesh);
    RenderMesh(Mesh&& mesh);
    ~RenderMesh();

    RenderMesh& operator=(const RenderMesh& other);
    RenderMesh& operator=(RenderMesh&& other);

private:
    void init();

private:
    Mesh m_MeshData;

    std::unique_ptr<VertexBuffer> m_VertexBuffer;
    std::unique_ptr<VertexBufferLayout> m_Layout;
};