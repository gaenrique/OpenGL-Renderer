#pragma once

#include "OpenGLWrappers/VertexArray.h"
#include "OpenGLWrappers/Shader.h"
#include "OpenGLWrappers/Texture.h"

// Singleton Renderer class used to render the VAO and Shader
class Renderer
{
public:
	// This ensures the Renderer data can't be copied since it is a singleton
	Renderer(const Renderer&) = delete;
	// Static Get function used to get the singular instance of the renderer
	static Renderer& Get()
	{
		return s_Instace;
	}

	void Draw(const VertexArray& va, const Shader& shader) const;

	void Draw(const VertexArray& va, const Shader& shader, const Texture& texture) const;

private:
	Renderer() {}

	static Renderer s_Instace;

};