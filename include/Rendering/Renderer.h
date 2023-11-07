#pragma once

#include "GLCall.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Objects/RenderObject.h"

class Renderer
{
public:
	Renderer();

	void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
	void draw(const RenderObject& object) const;

private:

};