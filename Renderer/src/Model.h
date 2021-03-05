#pragma once

#include <unordered_map>
#include <string>
#include <memory>

#include <glm/glm.hpp>

#include "OpenGLWrappers/VertexBufferLayout.h"
#include "OpenGLWrappers/VertexArray.h"
#include "OpenGLWrappers/Shader.h"
#include "OpenGLWrappers/Texture.h"

struct ModelAttributes
{
	glm::vec3 scale;
	float rotation;
	glm::vec3 rotationCoordinates;
	glm::vec3 position;
};

class Model
{
public:
	Model(const void* data, int dataSize, VertexBufferLayout& layout, const void* indices, int indicesSize);
	~Model();

	// When adding an instance of the model, the ModelAttributes are placed in
	// a map and the key is returned
	int AddInstance(glm::vec3 position, glm::vec3 scale, float rotation, glm::vec3 rotationCoordinates);

	inline std::shared_ptr<VertexArray> GetVAOP() const { return m_VAO; }
	inline std::shared_ptr<Shader> GetShaderP() const { return m_Shader; }
	inline std::shared_ptr<Texture> GetTextureP() const { return m_Texture; }

	inline const std::unordered_map<int, ModelAttributes> GetAttributes() const { return m_Instances; }

	inline unsigned int GetNumberOfVertices() const { return m_NumberOfVertices; }

	void AddShader(const std::string& filepath);

	void AddTexture(const std::string& filepath, const ImageFormat& imageFormat);

private:

	void GenerateVertexArray(const void* data, int dataSize, VertexBufferLayout& layout, const void* indices, int indicesSize);

	const unsigned int m_NumberOfVertices;
	std::shared_ptr<VertexArray> m_VAO;
	std::unordered_map<int, ModelAttributes> m_Instances;
	std::shared_ptr<Shader> m_Shader;
	std::shared_ptr<Texture> m_Texture;
	int m_CurrentIndex;
};
