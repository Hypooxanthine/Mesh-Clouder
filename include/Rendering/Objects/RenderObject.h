#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "Rendering/VertexArray.h"
#include "Rendering/IndexBuffer.h"
#include "Rendering/Shader.h"

class Renderer;

/**
 * @brief A RenderObject represents an object that can be drawn by the @ref Renderer.
 * 
 */
class RenderObject
{
public:
    RenderObject();
    virtual ~RenderObject() = default;

    void render(const Renderer& renderer) const;

    inline const VertexArray& getVertexArray() const { return *m_VertexArray; }
    inline const IndexBuffer& getIndexBuffer() const { return *m_IndexBuffer; }
    inline const Shader& getShader() const { return *m_Shader; }
    inline Shader& getShader() { return *m_Shader; }

    inline const glm::mat4& getTransform() const { return m_Transform; }
    inline const glm::vec3& getTranslation() const { return m_Translation; }
    inline const glm::mat4& getRotation() const { return m_Rotation; }
    inline const glm::vec3& getScale() const { return m_Scale; }

    void setTranslation(const glm::vec3& translation);
    void setRotation(const glm::vec3& rotation);
    void setRotation(const glm::mat4& rotation);
    void setScale(const glm::vec3& scale);

private:
    void computeTransform();

protected:
    std::unique_ptr<VertexArray> m_VertexArray = nullptr;
    std::unique_ptr<IndexBuffer> m_IndexBuffer = nullptr;
    std::unique_ptr<Shader> m_Shader = nullptr;

    glm::mat4 m_Transform = glm::mat4(1.f);
    glm::vec3 m_Translation = glm::vec3(0.f);
    glm::mat4 m_Rotation = glm::mat4(1.f);
    glm::vec3 m_Scale = glm::vec3(1.f);
};