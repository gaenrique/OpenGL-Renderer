#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include <vector>

struct Layout
{
	unsigned int index;
	int size;
	GLenum type;
	GLboolean normalized;
	GLsizei stride;
	const void* pointer;
};

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void Unbind() const;

	void AddVertexBuffer(VertexBuffer& vertexBuffer);
	void AddIndexBuffer(IndexBuffer& indexBuffer);

	void AddLayout(Layout& layout);

private:
	unsigned int m_RendererID;
	VertexBuffer* m_VertexBuffer;
	IndexBuffer* m_IndexBuffer;
};