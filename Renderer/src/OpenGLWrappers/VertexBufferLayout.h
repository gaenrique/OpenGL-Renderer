#pragma once

#include <vector>

#include <GL/glew.h>

// This LayoutElements struct contains elements needed for the creating of a VertexAttribPointer
struct LayoutElements {
	unsigned int type;
	unsigned int count;
	bool normalized;

	// Static function used to get the size of a GL type
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

	// This template is used to push attributes into the vector.
	// Template is used as there can be different data types
	// depending on the buffer
	template<typename T>
	void Push(unsigned int count) { }

	template<>
	void Push<float>(unsigned int count)
	{
		m_Elements.push_back({ GL_FLOAT, count, false });
		// Each time a new attribute is pushed, the stride is
		// increased by the size of the data type multiplied by the count
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
	
	// All layouts are pushed into this vector. They are initialised in a loop
	// in the VertexArray class
	std::vector<LayoutElements> m_Elements;

	// Keeps track of the current stride for the buffer
	unsigned int m_Stride;
};