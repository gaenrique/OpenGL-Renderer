#include "Camera.h"

#include "glm/gtc/matrix_transform.hpp"

Camera::Camera()
	: m_CameraSpeed(0.05f), m_ViewMatrix(glm::mat4(1.0f))
{
	InitialiseViewMatrix();
}

Camera::~Camera()
{

}

void Camera:: UpdateViewMatrix()
{
	m_ViewMatrix = glm::lookAt(m_CameraPos, m_CameraPos + m_CameraFront, m_CameraUp);
}

void Camera::MoveForward()
{
	m_CameraPos += m_CameraSpeed * m_CameraFront;
}

void Camera::MoveBackwards()
{
	m_CameraPos -= m_CameraSpeed * m_CameraFront;
}

void Camera::MoveRight()
{
	glm::vec3 right = glm::normalize(glm::cross(m_CameraFront, m_CameraUp));
	m_CameraPos += m_CameraSpeed * right;
}

void Camera::MoveLeft()
{
	glm::vec3 right = glm::normalize(glm::cross(m_CameraFront, m_CameraUp));
	m_CameraPos -= m_CameraSpeed * right;
}

void Camera::InitialiseViewMatrix()
{
	// The position of the camera in the world space
	m_CameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	m_CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	m_CameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	UpdateViewMatrix();
}