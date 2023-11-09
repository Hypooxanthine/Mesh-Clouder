#pragma once

#include "RenderObject.h"
#include "Data/Mesh.h"

/**
 * @brief A RenderMesh represents a mesh that can be drawn by the @ref Renderer class.
 * 
 */
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