#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "Rendering/Renderer.h"
#include "Rendering/Objects/Camera.h"
#include "Rendering/Objects/RenderMesh.h"
#include "Rendering/Objects/RenderPointCloud.h"
#include "Rendering/Objects/RenderGrid.h"
#include "Math/PointCloudProcessor.h"

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
    void render();

    /**
     * @brief Get the OpenGL texture id the scene was rendered on.
     * 
     * @return unsigned int The OpenGL texture id.
     */
    inline unsigned int getDrawnSceneTextureIndex() const { return m_Renderer.getRenderTextureID(); }

    /**
     * @brief Set the RenderMesh object
     * 
     * @param rm 
     */
    void setRenderMesh(const Mesh& m);

    /**
     * @brief Set the Render Meshobject
     * 
     * @param rm 
     */
    void setRenderMesh(Mesh&& m);

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

    /**
     * @brief Has to be triggered when user moved cursor.
     * 
     * @param x Mouse x RELATIVE TO VIEWPORT ORIGIN.
     * @param y Mouse y RELATIVE TO VIEWPORT ORIGIN.
     */
    void onMouseMoved(float x, float y);

private:
    void loadDefaultCube();

private:
    /* Rendering */
    Renderer m_Renderer;

    /* Scene */
    // Objects
    std::unique_ptr<RenderMesh> m_RenderMesh;
    std::unique_ptr<RenderPointCloud> m_RenderPointCloud;
    std::unique_ptr<RenderMesh> m_BrushMesh;
    std::unique_ptr<RenderGrid> m_CoordinateSystem;
    bool m_ShouldRenderBrush = false;

    // Camera
    Camera m_Camera;

    /* Editing */
    PointCloudProcessor m_Processor;

    /* Controls */
    float m_OrbitSpeed = 0.5f;
    float m_ZoomSpeed = 1.f;

    /* Context */
    glm::vec2 m_RenderTargetSize = { 800, 600 };
};