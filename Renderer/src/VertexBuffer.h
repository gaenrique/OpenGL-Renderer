#pragma once

class VertexBuffer
{
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetRendererID() { return m_RendererID; }

private:
	unsigned int m_RendererID;
};
