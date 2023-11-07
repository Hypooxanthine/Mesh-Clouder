#pragma once

#include <memory>

#include "Rendering/Renderer.h"
#include "Rendering/Objects/RenderMesh.h"

class ObjectEditor
{
public:
    ObjectEditor();
    ~ObjectEditor();

    void render() const;

    inline unsigned int getDrawnSceneTextureIndex() const { return m_Texture; }

    void setRenderMesh(const RenderMesh& rm);
    void setRenderMesh(RenderMesh&& rm);

private:
    void loadDefaultCube();

private:
    Renderer m_Renderer;
    unsigned int m_Texture;

    std::unique_ptr<RenderMesh> m_RenderMesh;
};