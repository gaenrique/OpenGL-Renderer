#pragma once

#include <GL/glew.h>
#include "../Logger/Logger.h"

#include <string>

#ifdef DEBUG_MODE

    #define ASSERT(x)\
        if (x) { }\
        else\
        {\
            __debugbreak();\
        }

    #define GLCall(x) GLClearError();\
        x;\
        ASSERT(GLCheckError(#x, __FILE__, __LINE__));

#else

    #define ASSERT(x)
    #define GLCall(x) x;

#endif


static void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

static bool GLCheckError(const char* function, const char* file, int line)
{
    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR)
    {
        Logger::Critical("[OpenGL Error]: ({}): Function {} at line {} at {}", error, function, line, file);
        return false;
    }
    return true;
}
