#pragma once

#include "Model.h"
#include "Camera.h"

#include <vector>
#include <memory>

#include "glm/glm.hpp"

class Scene
{
public:
	Scene(GLFWwindow* window);
	~Scene();

	void Draw();

	void AddModel(Model* model);

	inline std::vector<Model*> GetModels() { return m_Models; }
	inline glm::mat4 GetProjectionMatrix() { return m_ProjectionMatrix; }

private:

	GLFWwindow* m_Window;

	float m_DeltaTime;
	float m_LastFrame;

	Camera m_Camera;
	glm::mat4 m_ProjectionMatrix;
	std::vector<Model*> m_Models;
};