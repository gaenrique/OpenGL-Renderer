#include "Camera.h"

#include "glm/gtc/matrix_transform.hpp"

Camera::Camera()
{
	m_ViewMatrix = glm::mat4(1.0f);
	m_ViewMatrix = glm::translate(m_ViewMatrix, glm::vec3(0.0f, 0.0f, -3.0f));
}

Camera::~Camera()
{

}

void Camera::InitialiseProjectionMatrix()
{
	glm::mat4 m_ViewMatrix = glm::mat4(1.0f);
	m_ViewMatrix = glm::translate(m_ViewMatrix, glm::vec3(0.0f, 0.0f, 3.0f));
}