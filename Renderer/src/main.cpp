
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"

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

    std::cout << glGetString(GL_VERSION) << std::endl;

    float vertices[] = {
         -0.9f, -0.9f, 0.0f, 1.0f, 0.0f, 0.0f,
         0.9f, -0.9f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.0f, 0.9f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    unsigned int indices[] = {
        0, 1, 2
    };

    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(3);

    VertexArray VAO;
    VertexBuffer vb(vertices, sizeof(vertices));
    IndexBuffer ib(indices, sizeof(indices));
    VAO.AddVertexBuffer(vb, layout);
    VAO.AddIndexBuffer(ib);

    std::string filepath = "C:/dev/C++/Renderer/Renderer/Shaders/default.glsl";
    Shader shader(filepath);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        Renderer::Get().Draw(VAO, shader);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
 
    }

    glfwTerminate();
    return 0;
}