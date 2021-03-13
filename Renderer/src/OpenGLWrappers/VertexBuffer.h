#pragma once

class VertexBuffer
{
public:
	VertexBuffer(const void* data, unsigned int size);

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetID() { return m_RendererID; }

private:
	unsigned int m_RendererID;
};
