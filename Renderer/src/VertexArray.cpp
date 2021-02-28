#include "VertexArray.h"

#include "IndexBuffer.h"
#include "VertexBuffer.h"

#include <iostream>

VertexArray::VertexArray()
	: m_VertexBuffer(nullptr), m_IndexBuffer(nullptr)
{
	glGenVertexArrays(1, &m_RendererID);
	Bind();
	std::cout << "Vertex Array created. ID = " << m_RendererID << std::endl;
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}

void VertexArray::AddVertexBuffer(VertexBuffer& vertexBuffer)
{
	Bind();
	vertexBuffer.Bind();
	m_VertexBuffer = &vertexBuffer;
}

void VertexArray::AddIndexBuffer(IndexBuffer& indexBuffer)
{
	Bind();
	indexBuffer.Bind();
	m_IndexBuffer = &indexBuffer;
}

void VertexArray::AddLayout(Layout& layout)
{
	Bind();
	m_VertexBuffer->Bind();
	glEnableVertexAttribArray(layout.index);
	glVertexAttribPointer(layout.index, layout.size, layout.type, layout.normalized, layout.stride, layout.pointer);
}