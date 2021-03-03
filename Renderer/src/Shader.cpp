#include "Shader.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <fstream>
#include <istream>

#include <glm/gtc/type_ptr.hpp>

#include "Logger/Logger.h"

Shader::Shader(const std::string& filepath)
	: m_filepath(filepath)
{
	GenerateShaderObjects();
	ShaderSourceCode sourceCode = ParseShaders();
	// If the source code file fails to open
	if (sourceCode.vertexSource.empty())
	{
		Logger::Critical("File at {} failed to open", filepath);
		return;
	}
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
		Logger::Critical("Error while compiling shader: {}", (char*)&errorLog[0]);
		// Exit with failure.
		glDeleteShader(shader); // Don't leak the shader.
		return;
	}
	Logger::Info("Shader has compiled successfully!");

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
		Logger::Info("Shader Linking was successful!");
	}
}

void Shader::SetUniform1f(const std::string& uniformName, float f1)
{
	int uniformLocation = glGetUniformLocation(m_RendererID, uniformName.c_str());
	glUniform1f(uniformLocation, f1);
}

void Shader::SetUniform2f(const std::string& uniformName, float f1, float f2)
{
	int uniformLocation = glGetUniformLocation(m_RendererID, uniformName.c_str());
	glUniform2f(uniformLocation, f1, f2);
}

void Shader::SetUniform3f(const std::string& uniformName, float f1, float f2, float f3)
{
	int uniformLocation = glGetUniformLocation(m_RendererID, uniformName.c_str());
	glUniform3f(uniformLocation, f1, f2, f3);
}

void Shader::SetUniform4f(const std::string& uniformName, float f1, float f2, float f3, float f4)
{
	int uniformLocation = glGetUniformLocation(m_RendererID, uniformName.c_str());
	glUniform4f(uniformLocation, f1, f2, f3, f4);
}

void Shader::SetUniformMatrix4f(const std::string& uniformName, int numberOfMatrices, const glm::mat4& matrixData)
{
	int uniformLocation = glGetUniformLocation(m_RendererID, uniformName.c_str());
	glUniformMatrix4fv(uniformLocation, numberOfMatrices, GL_FALSE, glm::value_ptr(matrixData));
}

void Shader::Bind() const
{
	glUseProgram(m_RendererID);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}
