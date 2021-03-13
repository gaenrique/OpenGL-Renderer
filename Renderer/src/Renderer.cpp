#include "Renderer.h"

#include "ErrorHandling/ErrorHandling.h"

#include <GL/glew.h>

Renderer Renderer::s_Instace;

void Renderer::Draw(const Model& model) const
{
	model.GetVAOP()->Bind();
	model.GetShaderP()->Bind();
	model.GetTextureP()->Bind();
	//model.GetTextureP()->Bind();
	GLCall(glDrawElements(GL_TRIANGLES, model.GetNumberOfVertices(), GL_UNSIGNED_INT, 0));
}