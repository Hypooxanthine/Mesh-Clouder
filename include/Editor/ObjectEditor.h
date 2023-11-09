#pragma once

#include <memory>

#include "Rendering/Renderer.h"
#include "Rendering/Objects/RenderMesh.h"

#include "glm/glm.hpp"

/**
 * @brief ObjectEditor class is used to render viewport scene.
 * 
 */
class ObjectEditor
{
public:
    ObjectEditor();
    ~ObjectEditor();

    /**
     * @brief Deals with data each frame.
     * 
     */
    void update();

    /**
     * @brief Renders things on screen each frame.
     * 
     */
    void render() const;

    /**
     * @brief Get the OpenGL texture id the scene was rendered on.
     * 
     * @return unsigned int The OpenGL texture id.
     */
    inline unsigned int getDrawnSceneTextureIndex() const { return m_Texture; }

    /**
     * @brief Set the RenderMesh object
     * 
     * @param rm 
     */
    void setRenderMesh(const RenderMesh& rm);

    /**
     * @brief Set the Render Meshobject
     * 
     * @param rm 
     */
    void setRenderMesh(RenderMesh&& rm);

    /**
     * @brief Has to be triggered when viewport was resized.
     * 
     * @param x New viewport width.
     * @param y New viewport height.
     */
    void onWindowAspectRatioChanged(float x, float y);

    /**
     * @brief Has to be triggered when user dragged the cursor the viewport.
     * 
     * @param drag Dragging vector since last frame.
     */
    void onUserDrag(const glm::vec2& drag);

    /**
     * @brief Has to be triggered when user zoomed in/out in the viewport (mouse wheel).
     * 
     * @param value Zoom in value (positive for zooming in, negative for zooming out))
     */
    void onUserZoom(float value);

private:
    void loadDefaultCube();

    /**
     * @brief Computes model matrix from attribute parameters (none).
     * @todo Needs to be removed. It has nothing to do with the editor and should be handled for each object.
     * 
     */
    void computeModel();

    /// @brief Computes view matrix from attribute parameters (azimuth, elevation, view distance).
    void computeView();

    /// @brief Computes projection matrix from attribute parameters (fov, aspect ratio, near clip, far clip).
    void computeProjection();

    /// @brief Compute MVP (for vertices) and MV (for normals) matrices from model, view and projection matrices and updates shaders uniforms.
    void computeMVP();

private:
    Renderer m_Renderer;
    mutable unsigned int m_Texture;

    std::unique_ptr<RenderMesh> m_RenderMesh;

    // Controls
    float m_OrbitSpeed = 0.5f;
    float m_ZoomSpeed = 1.f;

    // Context
    glm::vec2 m_RenderTargetSize = { 800, 600 };

    // MVP model
    glm::mat4 m_MVPMatrix, m_MVMatrix;
    glm::mat4 m_ModelMatrix, m_ViewMatrix, m_ProjMatrix;

    // View
    float m_ViewAzimuth = 0.f;
    float m_ViewElevation = 0.001f;
    float m_ViewDistance = 20.f;

    // Projection
    float m_Fov = 45.f; // In degrees
    float m_AspectRatio = 800.f / 600.f;
    float m_NearClip = 0.1f;
    float m_FarClip = 10000.f;

};