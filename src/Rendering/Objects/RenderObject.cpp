#include "Rendering/Objects/RenderObject.h"

#include <glm/gtc/matrix_transform.hpp>

RenderObject::RenderObject()
{
    
}

void RenderObject::setTranslation(const glm::vec3& translation)
{
    m_Translation = translation;
    computeTransform();
}

void RenderObject::setRotation(const glm::vec3& rotation)
{
    glm::mat4 rotationX = glm::rotate(glm::mat4(1.f), rotation.x, glm::vec3(1.f, 0.f, 0.f));
    glm::mat4 rotationY = glm::rotate(glm::mat4(1.f), rotation.y, glm::vec3(0.f, 1.f, 0.f));
    glm::mat4 rotationZ = glm::rotate(glm::mat4(1.f), rotation.z, glm::vec3(0.f, 0.f, 1.f));
    computeTransform();
}

void RenderObject::setRotation(const glm::mat4& rotation)
{
    m_Rotation = rotation;
    computeTransform();
}

void RenderObject::setScale(const glm::vec3& scale)
{
    m_Scale = scale;
    computeTransform();
}

void RenderObject::computeTransform()
{
    glm::mat4 translation = glm::translate(glm::mat4(1.f), m_Translation);
    glm::mat4 scale = glm::scale(glm::mat4(1.f), m_Scale);

    m_Transform = translation * m_Rotation * scale;
}