#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"

#include <vector>
#include <memory>


class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void Unbind() const;

	void AddVertexBuffer(VertexBuffer& vertexBuffer, const VertexBufferLayout& layout);
	void AddIndexBuffer(IndexBuffer& indexBuffer);

private:
	unsigned int m_RendererID;
	unsigned int m_VertexBufferID;
	unsigned int m_IndexBufferID;
};