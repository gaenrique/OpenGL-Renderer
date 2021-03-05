#include "Model.h"

#include "OpenGLWrappers/VertexBuffer.h"
#include "OpenGLWrappers/IndexBuffer.h"
#include "Renderer.h"

#include "glm/gtc/matrix_transform.hpp"

Model::Model(const void* data, int dataSize, VertexBufferLayout& layout, const void* indices, int indicesSize)
	: m_NumberOfVertices(dataSize / sizeof(unsigned int))
{
	m_CurrentIndex = 0;
	GenerateVertexArray(data, dataSize, layout, indices, indicesSize);
}

Model::~Model()
{

}

void Model::Draw(glm::mat4 projectionMatrix, glm::mat4 viewMatrix) const
{
	m_Shader->Bind();
	m_Shader->SetUniformMatrix4f("projection", 1, projectionMatrix);
	m_Shader->SetUniformMatrix4f("view", 1, viewMatrix);
	for (std::pair<int, ModelAttributes> instance : m_Instances)
	{
		ModelAttributes attributes = instance.second;
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::scale(model, attributes.scale);
		model = glm::translate(model, attributes.position);
		model = glm::rotate(model, glm::radians(attributes.rotation), attributes.rotationCoordinates);
		m_Shader->SetUniformMatrix4f("model", 1, model);
		Renderer::Get().Draw(*this);
	}
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