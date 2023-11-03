#include "Rendering/Renderer.h"

Renderer::Renderer()
{
}

void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    va.bind();
    ib.bind();
    shader.bind();
    GLCall(glDrawElements(GL_TRIANGLES, (GLsizei)ib.getCount(), GL_UNSIGNED_INT, nullptr));
}
