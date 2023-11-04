#pragma once

#include <GL/glew.h>
#include <iostream>

#if defined(WIN32)
#define ASSERT(x) if(!(x)) __debugbreak();
#elif defined(__unix__)
#define ASSERT(x) if(!(x)) __builtin_trap();
#endif
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall())

inline void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

inline bool GLLogCall()
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << ")" << std::endl;
		return false;
	}

	return true;
}