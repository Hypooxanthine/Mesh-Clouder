#pragma once

#include "GLCall.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Objects/RenderObject.h"

/**
 * @brief Draws things with OpenGL.
 * 
 */
class Renderer
{
public:
	Renderer();

	/**
	 * @brief Performs a draw call with OpenGL using a @ref VertexArray, an @ref IndexBuffer and a @ref Shader.
	 * 
	 * @param va VertexArray instance.
	 * @param ib IndexBuffer instance.
	 * @param shader Shader instance.
	 */
	void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;

	/**
	 * @brief Performs a draw call with OpenGL using a @ref RenderObject.
	 * 
	 * @param object RenderObject instance.
	 */
	void draw(const RenderObject& object) const;

private:

};