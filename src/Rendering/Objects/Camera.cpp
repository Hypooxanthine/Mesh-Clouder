#include "Rendering/Objects/Camera.h"

#include <stdexcept>
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

const glm::vec3 Rotation::X_AXIS = glm::vec3(1.f, 0.f, 0.f);
const glm::vec3 Rotation::Y_AXIS = glm::vec3(0.f, 1.f, 0.f);
const glm::vec3 Rotation::Z_AXIS = glm::vec3(0.f, 0.f, 1.f);

Camera::Camera()
{
    requestComputeView();
    requestComputeProjection();
}

const glm::mat4 &Camera::getTransform() const
{
    if(m_ShouldComputeTransform) computeTransform();
    return m_Transform;
}

const glm::mat4 &Camera::getViewTransform() const
{
    if(m_ShouldComputeViewTransform) computeViewTransform();
    return m_ViewTransform;
}

const glm::mat4 &Camera::getProjectionTransform() const
{
    if(m_ShouldCumputeProjectionTransform) computeProjectionTransform();
    return m_ProjectionTransform;
}

const glm::vec3 &Camera::getTranslation() const
{
    return m_Translation;
}

const glm::mat4 &Camera::getRotation() const
{
    // When using orbiting, we need to compute rotation back from view transform so we're able to give the real value of rotation.
    if(isUsingOrbiting())
        m_Rotation = glm::translate(glm::mat4(1.f), m_Translation) * m_ViewTransform;
    
    return m_Rotation;
}

bool Camera::isUsingOrbiting() const
{
    return m_UseOrbiting;
}

float Camera::getViewAzimuth() const
{
    return m_ViewAzimuth;
}

float Camera::getViewElevation() const
{
    return m_ViewElevation;
}

float Camera::getViewDistance() const
{
    return m_ViewDistance;
}

float Camera::getFOV() const
{
    return m_Fov;
}

float Camera::getAspectRatio() const
{
    return m_AspectRatio;
}

float Camera::getNearClip() const
{
    return m_NearClip;
}

float Camera::getFarClip() const
{
    return m_FarClip;
}

void Camera::setTranslation(const glm::vec3 &translation)
{
    // When orbiting, we can set translation by setting focus point.
    if(isUsingOrbiting())
        throw std::runtime_error("You can't change camera translation manually while using camera orbiting.");

    m_Translation = translation;
    requestComputeView();
}

void Camera::setRotation(float angle, const glm::vec3 &axis)
{
    // When orbiting, we can set rotation by setting focus point, view distance, azimuth and elevation.
    if(isUsingOrbiting())
        throw std::runtime_error("You can't change camera rotation manually while using camera orbiting.");
    
    m_Rotation = glm::rotate(glm::mat4(1.f), angle, axis);
    requestComputeView();
}

void Camera::setRotation(const glm::mat4& rotation)
{
    // When orbiting, we can set rotation by setting focus point, view distance, azimuth and elevation.
    if(isUsingOrbiting())
        throw std::runtime_error("You can't change camera rotation manually while using camera orbiting.");
    
    m_Rotation = rotation;
    requestComputeView();
}

void Camera::setIsUsingOrbiting(bool val)
{
    if(m_UseOrbiting == val) return;

    // When switching orbiting/raw translation and rotation, we need to compute view and projection with the new camera mode.
    m_UseOrbiting = val;
    requestComputeView();
    requestComputeProjection();
}

void Camera::setViewAzimuth(float azimuth)
{
    m_ViewAzimuth = azimuth;

    static const float epsilon = 0.001f;

    while (m_ViewAzimuth > 360.f) m_ViewAzimuth -= 360.f;
    while (m_ViewAzimuth < 0.f) m_ViewAzimuth += 360.f;
    m_ViewElevation = glm::clamp(m_ViewElevation, epsilon, 180.f - epsilon);

    // We allow changing this while not using orbiting but there is no point computing view again because azimtuh won't be used in computation anyway.
    if(isUsingOrbiting())
        requestComputeView();
}

void Camera::setViewElevation(float elevation)
{
    m_ViewElevation = elevation;
    // We allow changing this while not using orbiting but there is no point computing view again because elevation won't be used in computation anyway.
    if(isUsingOrbiting())
        requestComputeView();
}

void Camera::setViewDistance(float distance)
{
    m_ViewDistance = distance;
    // We allow changing this while not using orbiting but there is no point computing view again because view distance won't be used in computation anyway.
    if(isUsingOrbiting())
        requestComputeView();
}

void Camera::setViewFocus(const glm::vec3& focus)
{
    m_ViewFocus = focus;
    // We allow changing this while not using orbiting but there is no point computing view again because focus point won't be used in computation anyway.
    if(isUsingOrbiting())
        requestComputeView();
}

void Camera::setFOV(float fov)
{
    m_Fov = fov;
    requestComputeProjection();
}

void Camera::setAspectRatio(float aspectRatio)
{
    m_AspectRatio = aspectRatio;
    std::cout << "New aspect ratio: " << m_AspectRatio << ".\n";

    requestComputeProjection();
}

void Camera::setNearClip(float nclip)
{
    m_NearClip = nclip;
    requestComputeProjection();
}

void Camera::setFarClip(float fclip)
{
    m_FarClip = fclip;
    requestComputeProjection();
}


void Camera::computeTransform() const
{
    std::cout << "Computing view-projection.\n";
    m_Transform = getProjectionTransform() * getViewTransform();
    m_ShouldComputeTransform = false;
}

void Camera::computeViewTransform() const
{
    std::cout << "Computing view.\n";
    // When using orbiting, we get the whole view transform from glm::lookAt. That's why we need to "remove" translation from it in getRotation()
    if(isUsingOrbiting())
    {
        m_Translation.x = m_ViewDistance * sin(glm::radians(m_ViewElevation)) * sin(glm::radians(m_ViewAzimuth));
        m_Translation.y = -m_ViewDistance * cos(glm::radians(m_ViewElevation));
        m_Translation.z = m_ViewDistance * sin(glm::radians(m_ViewElevation)) * cos(glm::radians(m_ViewAzimuth));
        
        m_ViewTransform = glm::lookAt(m_Translation, m_ViewFocus, glm::vec3(0.f, 1.f, 0.f));
    }
    else
    {
        m_ViewTransform = glm::translate(glm::mat4(1.f), m_Translation) * m_Rotation;
    }

    m_ShouldComputeViewTransform = false;
}

void Camera::computeProjectionTransform() const
{
    std::cout << "Computing projection.\n";
    m_ProjectionTransform = glm::perspective(m_Fov, m_AspectRatio, m_NearClip, m_FarClip);
    m_ShouldCumputeProjectionTransform = false;
}

void Camera::requestComputeView()
{
    m_ShouldComputeViewTransform = true;
    m_ShouldComputeTransform = true;
}

void Camera::requestComputeProjection()
{
    m_ShouldCumputeProjectionTransform = true;
    m_ShouldComputeTransform = true;
}
