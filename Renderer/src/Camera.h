#pragma once

#include "glm/glm.hpp"

class Camera
{
public:
	Camera();
	~Camera();

	inline glm::mat4 GetViewMatrix() { return m_ViewMatrix; }

private:
	void InitialiseProjectionMatrix();

	glm::vec3 m_CameraPos;
	glm::vec3 m_CameraTarget;
	glm::vec3 m_CameraDirection;
	glm::vec3 m_CameraUp;
	glm::vec3 m_CameraRight;
	glm::mat4 m_ViewMatrix;
};
