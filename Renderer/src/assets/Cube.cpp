#include "Cube.h"

Cube::Cube(glm::vec3 position, float rotation, glm::vec3 rotationCoordinates)
{
	m_Position = position;
	m_Rotation = rotation;
	m_RotationCoordinates = rotationCoordinates;
	CalculateModelViewProjection();
}

Cube::~Cube()
{

}

glm::mat4 Cube::CalculateModelMatrix()
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, m_Position);
	model = glm::rotate(model, glm::radians(m_Rotation), m_RotationCoordinates);
	return model;
}

glm::mat4 Cube::CalculateViewMatrix()
{
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	return view;
}

glm::mat4 Cube::CalculateProjectionMatrix()
{
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(45.0f, 1920.0f / 1080.0f, 0.1f, 100.0f);
	return projection;
}

void Cube::CalculateModelViewProjection()
{
	glm::mat4 model = CalculateModelMatrix();
	glm::mat4 view = CalculateViewMatrix();
	glm::mat4 projection = CalculateProjectionMatrix();
	m_MVPMatrix = projection * view * model;
}


