#include "Scene.h"

#include <memory>

#include "glm/gtc/matrix_transform.hpp"

Scene::Scene()
{
	m_ProjectionMatrix = glm::mat4(1.0f);
	m_ProjectionMatrix = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);
}

Scene::~Scene()
{

}

void Scene::AddModel(Model* model)
{
	m_Models.push_back(model);
}

void Scene::Draw()
{
	const float radius = 10.0f;
	float camX = sin(glfwGetTime()) * radius;
	float camZ = cos(glfwGetTime()) * radius;
	glm::mat4 view;
	view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	for (Model* model : m_Models)
	{
		model->Draw(m_ProjectionMatrix, view);
		//model->Draw(m_ProjectionMatrix, m_Camera.GetViewMatrix());
	}
}