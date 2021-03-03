#pragma once

#include <string>

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

	void SetUniform1f(std::string uniformName, float f1);
	void SetUniform2f(std::string uniformName, float f1, float f2);
	void SetUniform3f(std::string uniformName, float f1, float f2, float f3);
	void SetUniform4f(std::string uniformName, float f1, float f2, float f3, float f4);

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
