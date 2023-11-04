#pragma once

#include <GL/glew.h>
#include <iostream>

#include "Core/Assert.h"

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