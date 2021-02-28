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

	void AddVertexBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout);
	void AddIndexBuffer(const IndexBuffer& indexBuffer, const VertexBufferLayout& layout);

private:
	unsigned int m_RendererID;
	std::unique_ptr<VertexBuffer> m_VertexBuffer;
	std::unique_ptr<IndexBuffer> m_IndexBuffer;
};