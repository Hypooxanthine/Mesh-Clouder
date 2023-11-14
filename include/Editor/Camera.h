#pragma once

#include <glm/glm.hpp>

struct Rotation
{
    static const glm::vec3 X_AXIS;
    static const glm::vec3 Y_AXIS;
    static const glm::vec3 Z_AXIS;
};

class Camera
{
public:
    Camera();

    const glm::mat4& getTransform() const;
    const glm::mat4& getViewTransform() const;
    const glm::mat4& getProjectionTransform() const;
    const glm::vec3& getTranslation() const;

    /**
     * @brief Get the Rotation of the camera.
     * @warning When using orbiting, rotation computation is slower because it is recovered back from view transform (containing rotation and translation) and view translation.
     * 
     * @return const glm::mat4& 
     */
    const glm::mat4& getRotation() const;
    bool  isUsingOrbiting() const;
    float getViewAzimuth() const;
    float getViewElevation() const;
    float getViewDistance() const;
    const glm::vec3& getViewFocus() const;
    float getFOV() const;
    float getAspectRatio() const;
    float getNearClip() const;
    float getFarClip() const;

    void setTranslation(const glm::vec3& translation);

    /**
     * @brief Set camera rotation.
     * @see @ref Rotation for X, Y and Z axis static variables.
     * 
     * @param angle Rotation angle in degrees.
     * @param axis Axis to rotate around.
     */
    void setRotation(float angle, const glm::vec3& axis);
    void setRotation(const glm::mat4& rotation);
    void setIsUsingOrbiting(bool val);
    void setViewAzimuth(float azimuth);
    void setViewElevation(float elevation);
    void setViewDistance(float distance);
    void setViewFocus(const glm::vec3& focus);
    void setFOV(float fov);
    void setAspectRatio(float aspectRatio);
    void setNearClip(float nclip);
    void setFarClip(float fclip);

private:
    void computeTransform() const;
    void computeViewTransform() const;
    void computeProjectionTransform() const;

    void requestComputeView();
    void requestComputeProjection();

private:
    /* Transform matrices */
    mutable glm::mat4 m_Transform;
    mutable glm::mat4 m_ViewTransform, m_ProjectionTransform;

    // These variables are used to avoid recalculating matrices multiple times when their underlying values have not changed
    mutable bool m_ShouldComputeTransform = false;
    mutable bool m_ShouldComputeViewTransform = false;
    mutable bool m_ShouldCumputeProjectionTransform = false;

    // Raw transformations
    mutable glm::mat4 m_Rotation;
    mutable glm::vec3 m_Translation;

    // Computation values
    // View
        // Only for spherical coordinates
        // If false, uses rotation
        // If true, computes rotation from parameters
        bool m_UseOrbiting = false;
        float m_ViewAzimuth = -45.f;
        float m_ViewElevation = 135.f;
        float m_ViewDistance = 20.f;
        glm::vec3 m_ViewFocus;

    // Projection
    float m_Fov = 45.f; // In degrees
    float m_AspectRatio = 800.f / 600.f;
    float m_NearClip = 0.1f;
    float m_FarClip = 10000.f;
};