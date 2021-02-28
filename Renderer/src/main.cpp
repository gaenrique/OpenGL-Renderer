
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexArray.h"

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

    Layout vertexLayout = { 0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0 };
    Layout colorLayout = { 1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(3 * sizeof(float)) };

    VertexArray VAO;
    VertexBuffer vb(vertices, sizeof(vertices));
    VAO.AddVertexBuffer(vb);
    VAO.AddLayout(vertexLayout);
    VAO.AddLayout(colorLayout);

    std::string filepath = "C:/dev/C++/Renderer/Renderer/Shaders/default.glsl";
    Shader shader(filepath);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        shader.Bind();
        VAO.Bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
 
    }

    glfwTerminate();
    return 0;
}