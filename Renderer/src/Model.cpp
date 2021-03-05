#include "Model.h"

#include "OpenGLWrappers/VertexBuffer.h"
#include "OpenGLWrappers/IndexBuffer.h"

Model::Model(const void* data, int dataSize, VertexBufferLayout& layout, const void* indices, int indicesSize)
	: m_NumberOfVertices(dataSize / sizeof(unsigned int))
{
	m_CurrentIndex = 0;
	GenerateVertexArray(data, dataSize, layout, indices, indicesSize);
}

Model::~Model()
{

}

int Model::AddInstance(glm::vec3 position, glm::vec3 scale, float rotation, glm::vec3 rotationCoordinates)
{
	m_Instances.insert({ m_CurrentIndex, { scale, rotation, rotationCoordinates, position } });
	return m_CurrentIndex++;
}

void Model::GenerateVertexArray(const void* data, int dataSize, VertexBufferLayout& layout, const void* indices, int indicesSize)
{
	m_VAO = std::make_shared<VertexArray>();
	VertexBuffer vb(data, dataSize);
	m_VAO->AddVertexBuffer(vb, layout);
	IndexBuffer ib(indices, indicesSize);
	m_VAO->AddIndexBuffer(ib);
}

void Model::AddShader(const std::string& filepath)
{
	m_Shader = std::make_shared<Shader>(filepath);
}

void Model:: AddTexture(const std::string& filepath, const ImageFormat& imageFormat)
{
	m_Texture = std::make_shared<Texture>(filepath, imageFormat);
}