#include "Scene.h"

#include <memory>

#include "glm/gtc/matrix_transform.hpp"

Scene::Scene(GLFWwindow* window)
	: m_Window(window), m_DeltaTime(0.0f), m_LastFrame(0.0f)
{
	// The Windows User Pointer is used to store a pointer to the camera to use
	// on callbacks
	glfwSetWindowUserPointer(window, this);
	glfwSetCursorPosCallback(window, mouse_callback);
	m_ProjectionMatrix = glm::mat4(1.0f);
	m_ProjectionMatrix = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);
}

Scene::~Scene()
{

}

void Scene::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	Scene* scene = (Scene*)glfwGetWindowUserPointer(window);
	scene->m_Camera.OnCursorEvent(xpos, ypos);
}

void Scene::AddModel(Model* model)
{
	m_Models.push_back(model);
}

void Scene::Draw()
{
	float currentFrame = glfwGetTime();
	m_DeltaTime = currentFrame - m_LastFrame;
	m_LastFrame = currentFrame;

	m_Camera.Update(m_Window, m_DeltaTime);

	for (Model* model : m_Models)
	{
		model->Draw(m_ProjectionMatrix, m_Camera.GetViewMatrix());
	}
}