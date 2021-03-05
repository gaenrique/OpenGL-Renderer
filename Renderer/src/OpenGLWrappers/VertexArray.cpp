#include "VertexArray.h"

#include "IndexBuffer.h"
#include "VertexBuffer.h"

#include <iostream>

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_RendererID);
	Bind();
}

VertexArray::~VertexArray()
{
	glDeleteBuffers(GL_ARRAY_BUFFER, &m_VertexBufferID);
	glDeleteBuffers(GL_ELEMENT_ARRAY_BUFFER, &m_IndexBufferID);
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

void VertexArray::AddVertexBuffer(VertexBuffer& vertexBuffer, const VertexBufferLayout& layout)
{
	Bind();
	vertexBuffer.Bind();
	// A pointer is kept for the Vertex Buffer
	m_VertexBufferID = vertexBuffer.GetID();
	const auto& layoutElements = layout.GetElements();
	int offset = 0;
	for (int i = 0; i < layoutElements.size(); i++)
	{
		LayoutElements currentLayout = layoutElements[i];
		glEnableVertexAttribArray(i);
		// Variables in the struct are used to set up the AttribPointer, as well as the stride
		// kept in the VertexBufferLayout class and the offset calculated inside this function
		glVertexAttribPointer(i, currentLayout.count, currentLayout.type, currentLayout.normalized,
			layout.GetStride(), (void*)offset);
		// The offset increases each time a new attribute is added. The offset is incremented 
		// by the amount of elements multiplied by the size of the data type. The size of the
		// data type can be found using the static function in the VertexBufferLayout class
		offset += currentLayout.count * currentLayout.GetSizeOfType(currentLayout.type);
	}
}

void VertexArray::AddIndexBuffer(IndexBuffer& indexBuffer)
{
	Bind();
	indexBuffer.Bind();
	m_IndexBufferID = indexBuffer.GetID();
}