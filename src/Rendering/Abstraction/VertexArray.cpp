#include "Rendering/Abstraction/VertexArray.h"

#include "Rendering/GLCall.h"
#include "Rendering/Abstraction/VertexBuffer.h"
#include "Rendering/Abstraction/VertexBufferLayout.h"

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	vb.bind();
	GLCall(glBindVertexArray(m_RendererID));
	const auto& elements = layout.getElements();
	GLintptr offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(
			i, 
			element.count, 
			element.type, 
			element.normalized, 
			layout.getStride(), 
			(GLvoid*)offset
			));
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

void VertexArray::bind() const
{
	GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::unbind() const
{
	GLCall(glBindVertexArray(0));
}
