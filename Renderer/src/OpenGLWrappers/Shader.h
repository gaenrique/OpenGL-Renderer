#pragma once

#include <string>
#include <glm/glm.hpp>

class Shader
{

	struct ShaderSourceCode
	{
		std::string vertexSource;
		std::string fragmentSource;
	};


public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetProgramID() { return m_RendererID; }

	void SetUniform1f(const std::string& uniformName, float f1);
	void SetUniform2f(const std::string& uniformName, float f1, float f2);
	void SetUniform3f(const std::string& uniformName, float f1, float f2, float f3);
	void SetUniform4f(const std::string& uniformName, float f1, float f2, float f3, float f4);
	void SetUniformMatrix4f(const std::string& uniformName, int numberOfMatrices, const glm::mat4& matrixData);

private:
	const std::string m_filepath;

	unsigned int m_RendererID;
	unsigned int m_VertexID;
	unsigned int m_FragmentID;

	void GenerateShaderObjects();
	ShaderSourceCode ParseShaders();
	void CompileShaders(ShaderSourceCode shaderSourceCode);
	void CompileShader(const std::string& source, unsigned int shader);
	void CreateProgram();

	std::string GetShaderName();
};
