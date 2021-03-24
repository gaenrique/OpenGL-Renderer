#include "Camera.h"

#include "glm/gtc/matrix_transform.hpp"

#include <iostream>

Camera::Camera()
	: m_CameraSpeed(5.0f), m_ViewMatrix(glm::mat4(1.0f)), m_Sensitivity(0.1f), m_Yaw(-90.0f), m_LastX(1920/2), m_LastY(1080/2)
{
	InitialiseViewMatrix();
}

Camera::~Camera()
{

}

void Camera::OnCursorEvent(double xpos, double ypos)
{
	float xoffset = xpos - m_LastX;
	float yoffset = m_LastY - ypos;
	m_LastX = xpos;
	m_LastY = ypos;

	xoffset *= m_Sensitivity;
	yoffset *= m_Sensitivity;

	m_Yaw += xoffset;
	m_Pitch += yoffset;

	if (m_Pitch > 89.0f)
		m_Pitch = 89.0f;
	if (m_Pitch < -89.0f)
		m_Pitch = -89.0f;

	std::cout << xoffset << ", " << yoffset << std::endl;
}


void Camera::Update(GLFWwindow* window, float deltaTime)
{
	m_CameraDirection.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	m_CameraDirection.y = sin(glm::radians(m_Pitch));
	m_CameraDirection.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	m_CameraFront = glm::normalize(m_CameraDirection);

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