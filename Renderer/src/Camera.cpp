#include "Camera.h"

#include "glm/gtc/matrix_transform.hpp"

Camera::Camera()
	: m_CameraSpeed(5.0f), m_ViewMatrix(glm::mat4(1.0f))
{
	InitialiseViewMatrix();
}

Camera::~Camera()
{

}

void Camera::Update(GLFWwindow* window, float deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		MoveForward(deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		MoveBackwards(deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		MoveLeft(deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		MoveRight(deltaTime);
	}
	UpdateViewMatrix();
}

void Camera:: UpdateViewMatrix()
{
	m_ViewMatrix = glm::lookAt(m_CameraPos, m_CameraPos + m_CameraFront, m_CameraUp);
}

void Camera::MoveForward(float deltaTime)
{
	m_CameraPos += m_CameraSpeed * m_CameraFront * deltaTime;
}

void Camera::MoveBackwards(float deltaTime)
{
	m_CameraPos -= m_CameraSpeed * m_CameraFront * deltaTime;
}

void Camera::MoveRight(float deltaTime)
{
	glm::vec3 right = glm::normalize(glm::cross(m_CameraFront, m_CameraUp));
	m_CameraPos += m_CameraSpeed * right * deltaTime;
}

void Camera::MoveLeft(float deltaTime)
{
	glm::vec3 right = glm::normalize(glm::cross(m_CameraFront, m_CameraUp));
	m_CameraPos -= m_CameraSpeed * right * deltaTime;
}

void Camera::InitialiseViewMatrix()
{
	// The position of the camera in the world space
	m_CameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	m_CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	m_CameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	UpdateViewMatrix();
}