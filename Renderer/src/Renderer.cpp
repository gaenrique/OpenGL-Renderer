#include "Renderer.h"

#include <GL/glew.h>

Renderer Renderer::s_Instace;

void Renderer::Draw(const VertexArray& va, const Shader& shader) const
{
	va.Bind();
	shader.Bind();
	glDrawElements(GL_TRIANGLES, va.GetNumberOfVertices(), GL_UNSIGNED_INT, 0);
}

void Renderer::Draw(const VertexArray& va, const Shader& shader, const Texture& texture) const
{
	texture.Bind();
	va.Bind();
	shader.Bind();
	glDrawElements(GL_TRIANGLES, va.GetNumberOfVertices(), GL_UNSIGNED_INT, 0);
}