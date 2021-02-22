#pragma once

class VertexBuffer
{
public:
	VertexBuffer();
	VertexBuffer(const void* data, unsigned int count);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

	void InsertData(const void* data, unsigned int count);
private:
	unsigned int m_RendererID;
};
