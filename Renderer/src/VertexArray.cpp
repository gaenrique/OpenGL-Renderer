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

void VertexArray::AddVertexBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout)
{
	Bind();
	vertexBuffer.Bind();
	m_VertexBuffer = std::make_unique<VertexBuffer>(vertexBuffer);
	const auto& layoutElements = layout.GetElements();
	int offset = 0;
	for (int i = 0; i < layoutElements.size(); i++)
	{
		LayoutElements currentLayout = layoutElements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, currentLayout.count, currentLayout.type, currentLayout.normalized,
			layout.GetStride(), (void*)offset);
		offset += currentLayout.count * currentLayout.GetSizeOfType(currentLayout.type);
	}
}

void VertexArray::AddIndexBuffer(const IndexBuffer& indexBuffer, const VertexBufferLayout& layout)
{
	Bind();
	indexBuffer.Bind();
	m_IndexBuffer = std::make_unique<IndexBuffer>(indexBuffer);
}