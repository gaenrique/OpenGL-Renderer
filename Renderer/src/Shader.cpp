#include "Shader.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <istream>

Shader::Shader(const std::string& filepath)
	: m_filepath(filepath)
{
	GenerateShaderObjects();
}

Shader::~Shader()
{

}

void Shader::GenerateShaderObjects()
{
	m_VertexID = glCreateShader(GL_VERTEX_SHADER);
	m_FragmentID = glCreateShader(GL_FRAGMENT_SHADER);
}


// This functions is used to parse the shader file and return a struct containing the two
// separate source code strings. This has to be done this way as both the vertex and fragment
// shader are stored in the same file. They can be differentiated by '#vertex shader' and '#fragment shader'
Shader::ShaderFragmentSource Shader::ParseShaders()
{
	std::ifstream stream;

	// Opening file as an stream to read from
	stream.open(m_filepath, std::ios_base::in);

	// This enum is used to index into the array containing the two source code strings
	enum ShaderType
	{
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};

	ShaderType currentShader = NONE;

	// This array contains the source code for the vertex shader and fragment shader
	std::string sourceCode[2];
	std::string currentLine;

	while (std::getline(stream, currentLine))
	{
		if (currentLine.find("#"))
		{
			if (currentLine.find("vertex"))
			{
				currentShader = VERTEX;
			}
			else if (currentLine.find("fragment"))
			{
				currentShader = FRAGMENT;
			}
		}
		else
		{
			if (currentShader != NONE)
			{
				currentLine.append("\n");
				sourceCode[(int)currentShader].append(currentLine);
			}
		}
	}

	return { sourceCode[0], sourceCode[1] };
}

void Shader::CompileShaders()
{

}

void Shader::Bind() const
{

}

void Shader::Unbind() const
{

}
