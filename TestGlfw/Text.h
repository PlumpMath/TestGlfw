#pragma once
#include <string>
#include <glad/glad.h>
#include "Shader.h"
class Font;

class Text
{
public:
	Text();
	~Text();
	void SetShader(Shader& shader);
	void SetFont(Font& font);
	void SetString(const std::string& text);
	void Render(Shader &shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);

	Font* m_Font;
	std::string m_Text;
	GLuint VAO, VBO;
	Shader* m_Shader;
};

