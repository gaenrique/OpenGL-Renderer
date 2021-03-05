#pragma once

class IndexBuffer
{
public:
	IndexBuffer(const void* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	void InsertData(const void* data, unsigned int count);

	inline unsigned int GetNumberOfVertices() const { return m_NumberOfVertices; }
private:
	unsigned int m_RendererID;
	unsigned int m_NumberOfVertices;
};
