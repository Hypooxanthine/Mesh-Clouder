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
    RenderMesh(const RenderMesh& other) = delete;
    RenderMesh(RenderMesh&& other) = delete;
    virtual ~RenderMesh();

    RenderMesh& operator=(const RenderMesh& other) = delete;
    RenderMesh& operator=(RenderMesh&& other) = delete;

    virtual void render(const Renderer& renderer, const Camera& camera) const override;

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
