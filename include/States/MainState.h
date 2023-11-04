#pragma once

#include "States/State.h"

#include "Rendering/Renderer.h"

#include <memory>

class Mesh;

class MainState : public State
{
public:
    MainState();
    ~MainState();

    virtual void update() override;
    virtual void render() override;
    virtual void renderImGui() override;

private:
    void importMesh();

private:
    bool m_ShouldImportMesh = false;

    bool m_MeshLoaded = false;
    std::unique_ptr<Mesh> m_Mesh;

    Renderer m_Renderer;

    std::unique_ptr<VertexArray> va;
    std::unique_ptr<VertexBuffer> vb;
    std::unique_ptr<VertexBufferLayout> layout;
    std::unique_ptr<IndexBuffer> ib;

    std::unique_ptr<Shader> shader;
    unsigned int texture;
};