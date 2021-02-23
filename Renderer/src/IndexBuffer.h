#pragma once

class IndexBuffer
{
public:
	IndexBuffer();
	IndexBuffer(const void* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	void InsertData(const void* data, unsigned int count);
private:
	unsigned int m_RendererID;
};
