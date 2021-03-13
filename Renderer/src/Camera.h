#pragma once

#include "glm/glm.hpp"

class Camera
{
public:
	Camera();
	~Camera();

	inline const glm::vec3 GetCameraPosition() const { return m_CameraPos; }
	inline const glm::vec3 GetCameraFront() const { return m_CameraFront; }
	inline const glm::vec3 GetCameraUp() const { return m_CameraUp; }
	inline const glm::mat4 GetViewMatrix() const { return m_ViewMatrix; }

	void UpdateViewMatrix();

	void MoveForward();
	void MoveBackwards();
	void MoveRight();
	void MoveLeft();

private:
	void InitialiseViewMatrix();

	float m_CameraSpeed;
	glm::vec3 m_CameraPos;
	glm::vec3 m_CameraFront;
	glm::vec3 m_CameraUp;
	glm::mat4 m_ViewMatrix;
};
