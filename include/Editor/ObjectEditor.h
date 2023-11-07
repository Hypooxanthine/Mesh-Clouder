#pragma once

#include <memory>

#include "Rendering/Renderer.h"
#include "Rendering/Objects/RenderMesh.h"

#include "glm/glm.hpp"

class ObjectEditor
{
public:
    ObjectEditor();
    ~ObjectEditor();

    void update();
    void render() const;

    inline unsigned int getDrawnSceneTextureIndex() const { return m_Texture; }

    void setRenderMesh(const RenderMesh& rm);
    void setRenderMesh(RenderMesh&& rm);

    void onWindowAspectRatioChanged(float x, float y);
    void onUserDrag(const glm::vec2& drag);
    void onUserZoom(float value);

private:
    void loadDefaultCube();

    void computeModel();
    void computeView();
    void computeProjection();
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