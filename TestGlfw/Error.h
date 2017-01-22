#pragma once
#include <iostream>
#include "glad/glad.h"

static void err(const std::string& msg)
{
	std::cout << msg.c_str() << std::endl;
	std::cin.get();
}

static void check_gl_err()
{
	if(glGetError() != GL_NO_ERROR)
	{
		err("GL ERROR: " + std::string("" + glGetError()));
	}
}

static GLenum glCheckError_(const char *file, int line)
{
	GLenum errorCode;
	while ((errorCode = glGetError()) != GL_NO_ERROR)
	{
		std::string error;
		switch (errorCode)
		{
		case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
		case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
		case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
		case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
		case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
		case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
		case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
		}
		std::cout << error << " | " << file << " (" << line << ")" << std::endl;
	}
	return errorCode;
}

//#ifdef DEBUG
#define glCheckError() glCheckError_(__FILE__, __LINE__) 
/*#else
#define glCheckError()
#endif*/