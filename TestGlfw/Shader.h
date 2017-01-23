#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include "glad/glad.h"
#include <glm/mat4x2.hpp>
#include "NonCopyable.h"

class Shader : NonCopyable
{
public:
	Shader() = default;
	~Shader();

	GLuint m_program;
	void Load(const std::string& vertexPath, const std::string& fragmentPath);
	void Use();

	std::string m_name = "UNKNOWN";

	GLint GetUniLocation(const GLchar* name);

	void    SetFloat(const GLchar *name, GLfloat value, GLboolean useShader = false);
	void    SetInteger(const GLchar *name, GLint value, GLboolean useShader = false);
	void    SetVector2f(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader = false);
	void    SetVector2f(const GLchar *name, const glm::vec2 &value, GLboolean useShader = false);
	void    SetVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
	void    SetVector3f(const GLchar *name, const glm::vec3 &value, GLboolean useShader = false);
	void    SetVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
	void    SetVector4f(const GLchar *name, const glm::vec4 &value, GLboolean useShader = false);
	void    SetMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader = false);
};

