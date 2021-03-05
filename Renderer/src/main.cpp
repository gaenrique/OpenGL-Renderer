
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "OpenGLWrappers/Shader.h"
#include "OpenGLWrappers/VertexBuffer.h"
#include "OpenGLWrappers/VertexArray.h"
#include "OpenGLWrappers/VertexBufferLayout.h"
#include "Renderer.h"
#include "Logger/Logger.h"
#include "OpenGLWrappers/Texture.h"
#include "assets/Cube.h"
#include "Model.h"

#include <iostream>


static void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

static void GLCheckError()
{
    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR)
    {
        std::cout << "[OpenGL Error] (" << error << ")" << std::endl;
    }
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1920, 1080, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;

    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        // This code runs if glew failed to initialise
        std::cout << "Glew failed to initialise :(" << std::endl;
    }

    glEnable(GL_DEPTH_TEST);

    Logger::Info("OpenGL Version: {}", glGetString(GL_VERSION));

    float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    unsigned int indices[] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19,
        20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35
    };
        

    Cube cubes[] = {
        { glm::vec3(0.0f, 0.0f, 0.0f), 20.0f, glm::vec3(0.8f, 0.2f, 0.3f) },
        { glm::vec3(2.0f, 5.0f, -15.0f), 20.0f, glm::vec3(0.8f, 0.2f, 0.3f) },
        { glm::vec3(-1.5f, -2.2f, -2.5f), 20.0f, glm::vec3(0.8f, 0.2f, 0.3f) },
        { glm::vec3(-3.8f, -2.0f, -12.3f), 20.0f, glm::vec3(0.8f, 0.2f, 0.3f) },
        { glm::vec3(2.4f, -0.4f, -3.5f), 20.0f, glm::vec3(0.8f, 0.2f, 0.3f) },
        { glm::vec3(-1.7f, 3.0f, -7.5f), 20.0f, glm::vec3(0.8f, 0.2f, 0.3f) },
        { glm::vec3(1.3f, -2.0f, -2.5f), 20.0f, glm::vec3(0.8f, 0.2f, 0.3f) },
        { glm::vec3(1.5f, 2.0f, -2.5f), 20.0f, glm::vec3(0.8f, 0.2f, 0.3f) },
        { glm::vec3(1.5f, 0.2f, -1.5f), 20.0f, glm::vec3(0.8f, 0.2f, 0.3f) },
        { glm::vec3(-1.3f, 1.0f, -1.5f), 20.0f, glm::vec3(0.8f, 0.2f, 0.3f) }
    };

    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(2);

    Model model(vertices, sizeof(vertices), layout, indices, sizeof(indices));

    model.AddInstance(glm::vec3(0.0f, 0.0f, -2.0f), glm::vec3(1.0f, 1.0f, 1.0f), 45.0f, glm::vec3(1.0f, 0.5f, 0.5f));
    model.AddShader("C:/dev/C++/OpenGL-Renderer/Renderer/Shaders/default.glsl");
    model.AddTexture("C:/dev/C++/OpenGL-Renderer/Renderer/Textures/grass.jpg", ImageFormat::JPEG);

    /* Loop until the user closes the window */

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        auto va = model.GetVAOP();
        va->Bind();   
        model.GetShaderP()->Bind();
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);
        model.GetShaderP()->SetUniformMatrix4f("projection", 1, projection);
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        model.GetShaderP()->SetUniformMatrix4f("view", 1, view);

        auto instance = model.GetAttributes();
        for (std::pair<int, ModelAttributes> element : instance)
        {
            ModelAttributes attributes = element.second;
            glm::mat4 modelM = glm::mat4(1.0f);
            modelM = glm::translate(modelM, attributes.position);
            modelM = glm::rotate(modelM, glm::radians(attributes.rotation), attributes.rotationCoordinates);
            model.GetShaderP()->SetUniformMatrix4f("model", 1, modelM);
            Renderer::Get().Draw(model);
        }

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
 
    }

    glfwTerminate();
    return 0;
}