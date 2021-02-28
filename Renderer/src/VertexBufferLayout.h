#pragma once

#include <vector>

#include <GL/glew.h>

struct LayoutElements {
	unsigned int type;
	unsigned int count;
	bool normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
			case GL_FLOAT:			return sizeof(float);
			case GL_UNSIGNED_INT:   return sizeof(unsigned int);
			case GL_UNSIGNED_BYTE:  return sizeof(unsigned char);
		}
		return 0;
	}
};

class VertexBufferLayout {
public:
	VertexBufferLayout()
		: m_Stride(0) { }

	template<typename T>
	void Push(unsigned int count) { }

	template<>
	void Push<float>(unsigned int count)
	{
		m_Elements.push_back({ GL_FLOAT, count, false });
		m_Stride += sizeof(float) * count;
	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT, count, false });
		m_Stride += sizeof(unsigned int) * count;
	}

	template<>
	void Push<unsigned char>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, true });
		m_Stride += sizeof(unsigned char) * count;
	}

	inline unsigned int GetStride() const { return m_Stride; }

	inline std::vector<LayoutElements> GetElements() const { return m_Elements; }

private:
	
	std::vector<LayoutElements> m_Elements;
	unsigned int m_Stride;
};