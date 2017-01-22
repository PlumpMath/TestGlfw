#pragma once
#include <glad/glad.h>
#include <iostream>
#include <string>

static bool Log(const char* function, const char* file, int line)
{
	auto error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::string errMsg;
		switch (error)
		{
		case GL_INVALID_OPERATION:      errMsg = "INVALID_OPERATION";      break;
		case GL_INVALID_ENUM:           errMsg = "INVALID_ENUM";           break;
		case GL_INVALID_VALUE:          errMsg = "INVALID_VALUE";          break;
		case GL_OUT_OF_MEMORY:          errMsg = "OUT_OF_MEMORY";          break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:  errMsg = "INVALID_FRAMEBUFFER_OPERATION";  break;
		case GL_STACK_OVERFLOW:                errMsg = "STACK_OVERFLOW"; break;
		case GL_STACK_UNDERFLOW:               errMsg = "STACK_UNDERFLOW"; break;
		default: errMsg = "Unknown (" + std::to_string(error) + ")";
		}
		std::cout << "[OpenGL Error] (" << errMsg << "): " << function << " " << file << ":" << std::to_string(line) << std::endl;
		return false;
	}
	return true;
}


#define GLCall(x)\
		x; \
		if (!Log(#x, __FILE__, __LINE__)) __debugbreak();
/*#else
#define GLCall(x) x
#endif*/
