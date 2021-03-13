#include "IndexBuffer.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../ErrorHandling/ErrorHandling.h"

IndexBuffer::IndexBuffer(const void* data, unsigned int size)
	:m_NumberOfVertices(size / sizeof(unsigned int))
{
	GLCall(glGenBuffers(1, &m_RendererID));
	InsertData(data, size);
}


void IndexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void IndexBuffer::InsertData(const void* data, unsigned int size)
{
	Bind();
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}