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
    RenderMesh();
    RenderMesh(const RenderMesh& other);
    RenderMesh(RenderMesh&& other);
    RenderMesh(const Mesh& mesh);
    RenderMesh(Mesh&& mesh);
    virtual ~RenderMesh();

    RenderMesh& operator=(const RenderMesh& other);
    RenderMesh& operator=(RenderMesh&& other);

    inline const Mesh& getMeshData() const { return m_MeshData; }

    void setMesh(const Mesh& mesh);
    void setMesh(Mesh&& mesh);

private:
    void init();

protected:
    std::unique_ptr<VertexBuffer> m_VertexBuffer;
    std::unique_ptr<VertexBufferLayout> m_Layout;

private:
    Mesh m_MeshData;

};