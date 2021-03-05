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

	glm::mat4 m_ViewMatrix;
};
