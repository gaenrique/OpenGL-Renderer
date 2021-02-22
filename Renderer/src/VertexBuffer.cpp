#include "VertexBuffer.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

VertexBuffer::VertexBuffer()
{
	glGenBuffers(1, &m_RendererID);
}

VertexBuffer::VertexBuffer(const void* data, unsigned int count)
{
	glGenBuffers(1, &m_RendererID);
	InsertData(data, count);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::InsertData(const void* data, unsigned int count)
{
	Bind();
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * count, data, GL_STATIC_DRAW);
}