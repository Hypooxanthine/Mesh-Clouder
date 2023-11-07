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

    void onWindowAspectRatioChanged(float aspectRation);

private:
    void loadDefaultCube();
    void computeMVP();

private:
    Renderer m_Renderer;
    mutable unsigned int m_Texture;

    std::unique_ptr<RenderMesh> m_RenderMesh;

    glm::mat4 m_MVPMatrix, m_MVMatrix;
    glm::mat4 m_ModelMatrix, m_ViewMatrix, m_ProjMatrix;
    float m_Fov = 45.f; // In degrees
    float m_AspectRatio = 800.f / 600.f;
    float m_NearClip = 0.1f;
    float m_FarClip = 10000.f;

};