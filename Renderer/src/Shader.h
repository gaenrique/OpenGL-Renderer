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

private:
	const std::string m_filepath;

	unsigned int m_RendererID;
	unsigned int m_VertexID;
	unsigned int m_FragmentID;

	void GenerateShaderObjects();
	ShaderSourceCode ParseShaders();
	void CompileShaders();
};
