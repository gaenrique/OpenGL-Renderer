#include "Shader.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <fstream>
#include <istream>

Shader::Shader(const std::string& filepath)
	: m_filepath(filepath)
{
	GenerateShaderObjects();
	ShaderSourceCode sourceCode = ParseShaders();
	CompileShaders(sourceCode);
	CreateProgram();
}

Shader::~Shader()
{
	glDeleteProgram(m_RendererID);
}

void Shader::GenerateShaderObjects()
{
	m_VertexID = glCreateShader(GL_VERTEX_SHADER);
	m_FragmentID = glCreateShader(GL_FRAGMENT_SHADER);
}


// This functions is used to parse the shader file and return a struct containing the two
// separate source code strings. This has to be done this way as both the vertex and fragment
// shader are stored in the same file. They can be differentiated by '#vertex shader' and '#fragment shader'
Shader::ShaderSourceCode Shader::ParseShaders()
{
	std::ifstream stream;

	// Opening file as an stream to read from
	stream.open(m_filepath, std::ios_base::in);

	if (!stream.is_open())
	{
		std::cout << "File '" << m_filepath << "' failed to open" << std::endl;
		stream.close();
		return { nullptr, nullptr };
	}

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
		if (currentLine.find("#") != std::string::npos)
		{
			if (currentLine.find("vertex") != std::string::npos)
			{
				currentShader = VERTEX;
				// continue keyword is used to skip to the next line in order to not append it
				continue;
			}
			else if (currentLine.find("fragment") != std::string::npos)
			{
				currentShader = FRAGMENT;
				continue;
			}
		}
		if (currentShader != NONE)
		{
			currentLine.append("\n");
			// Enum is used to index into the source code array
			sourceCode[(int)currentShader].append(currentLine);
		}
	}

	sourceCode[0].append("\0");
	sourceCode[1].append("\0");

	return { sourceCode[0], sourceCode[1] };
}

void Shader::CompileShaders(ShaderSourceCode shaderSourceCode)
{
	CompileShader(shaderSourceCode.vertexSource, m_VertexID);
	CompileShader(shaderSourceCode.fragmentSource, m_FragmentID);
}

void Shader::CompileShader(const std::string& source, unsigned int shader)
{
	// Get strings for glShaderSource.
	const char* c_str = source.c_str();
	glShaderSource(shader, 1, &c_str, NULL);

	glCompileShader(shader);

	GLint isCompiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);

		// Provide the infolog in whatever manor you deem best.
		std::cout << "Error while compiling shader: " << errorLog[0] << std::endl;
		// Exit with failure.
		glDeleteShader(shader); // Don't leak the shader.
		return;
	}
	std::cout << "Shader has compiled successfully" << std::endl;

	// Shader compilation is successful.
}

void Shader::CreateProgram()
{
	m_RendererID = glCreateProgram();
	glAttachShader(m_RendererID, m_VertexID);
	glAttachShader(m_RendererID, m_FragmentID);
	glLinkProgram(m_RendererID);
	int success;
	glGetProgramiv(m_RendererID, GL_LINK_STATUS, &success);
	if (success)
	{
		std::cout << "Linking was successful!" << std::endl;

	}
}

void Shader::Bind() const
{
	glUseProgram(m_RendererID);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}
