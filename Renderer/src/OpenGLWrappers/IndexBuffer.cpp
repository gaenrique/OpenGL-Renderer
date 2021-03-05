#include "IndexBuffer.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

IndexBuffer::IndexBuffer(const void* data, unsigned int size)
	:m_NumberOfVertices(size / sizeof(unsigned int))
{
	glGenBuffers(1, &m_RendererID);
	InsertData(data, size);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::InsertData(const void* data, unsigned int size)
{
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}