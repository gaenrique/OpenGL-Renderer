#pragma once

class IndexBuffer
{
public:
	IndexBuffer(const void* data, unsigned int size);

	void Bind() const;
	void Unbind() const;

	void InsertData(const void* data, unsigned int count);
	inline unsigned int GetID() const { return m_RendererID; }
private:
	unsigned int m_RendererID;
	unsigned int m_NumberOfVertices;
};
