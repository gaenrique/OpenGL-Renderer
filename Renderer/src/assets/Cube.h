#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Cube
{
public:
	Cube(glm::vec3 position, float rotation, glm::vec3 rotationCoordinates);
	~Cube();

	inline glm::mat4 GetMVPMatrix() const { return m_MVPMatrix;}

private:
	glm::mat4 CalculateModelMatrix();
	glm::mat4 CalculateViewMatrix();
	glm::mat4 CalculateProjectionMatrix();
	void CalculateModelViewProjection();

	glm::vec3 m_Position;
	float m_Rotation;
	glm::vec3 m_RotationCoordinates;
	glm::mat4 m_MVPMatrix;
};
