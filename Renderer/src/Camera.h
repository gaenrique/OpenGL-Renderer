#pragma once

#include "glm/glm.hpp"
#include <GLFW/glfw3.h>

class Camera
{
public:
	Camera();
	~Camera();

	inline const glm::vec3 GetCameraPosition() const { return m_CameraPos; }
	inline const glm::vec3 GetCameraFront() const { return m_CameraFront; }
	inline const glm::vec3 GetCameraUp() const { return m_CameraUp; }
	inline const glm::mat4 GetViewMatrix() const { return m_ViewMatrix; }

	void Update(GLFWwindow* window, float deltaTime);

	void MoveForward(float deltaTime);
	void MoveBackwards(float deltaTime);
	void MoveRight(float deltaTime);
	void MoveLeft(float deltaTime);

private:
	void InitialiseViewMatrix();
	void UpdateViewMatrix();

	float m_CameraSpeed;
	glm::vec3 m_CameraPos;
	glm::vec3 m_CameraFront;
	glm::vec3 m_CameraUp;
	glm::mat4 m_ViewMatrix;
};
