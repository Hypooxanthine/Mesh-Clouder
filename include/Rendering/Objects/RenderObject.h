#pragma once

#include <memory>

#include "Rendering/VertexArray.h"
#include "Rendering/IndexBuffer.h"
#include "Rendering/Shader.h"

/**
 * @brief A RenderObject represents an object that can be drawn by the @ref Renderer.
 * 
 */
class RenderObject
{
public:
    RenderObject();
    ~RenderObject() = default;

    inline const VertexArray& getVertexArray() const { return *m_VertexArray; }
    inline const IndexBuffer& getIndexBuffer() const { return *m_IndexBuffer; }
    inline const Shader& getShader() const { return *m_Shader; }
    inline Shader& getShader() { return *m_Shader; }

protected:
    std::unique_ptr<VertexArray> m_VertexArray = nullptr;
    std::unique_ptr<IndexBuffer> m_IndexBuffer = nullptr;
    std::unique_ptr<Shader> m_Shader = nullptr;
};