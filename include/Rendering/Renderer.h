#pragma once

#include <glm/glm.hpp>

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
	~Renderer();

	/**
	 * @brief Has to be called before any rendering of current frame.
	 * 
	 */
	void beginScene();

	/**
	 * @brief Has to be called after any rendering scene.
	 * @warning Everything sent to draw functions need to be still alive when calling endScene.
	 * 
	 */
	void endScene();

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

	void setViewport(const glm::vec<2, unsigned int>& o, const glm::vec<2, unsigned int>& s);
	void setViewportOrigin(const glm::vec<2, unsigned int>& o);
	void setViewportSize(const glm::vec<2, unsigned int>& s);

	inline unsigned int getRenderTextureID() const { return m_RenderTexture; }

private:
	glm::vec<2, unsigned int> m_ViewportOrigin;
	glm::vec<2, unsigned int> m_ViewportSize;
	
	// For drawing onto a texture
    unsigned int m_RenderTexture;
	unsigned int m_Fbo, m_Rbo;
};