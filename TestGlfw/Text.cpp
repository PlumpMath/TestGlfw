#include "Text.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include "Font.h"
#include <glm/gtc/matrix_transform.inl>
#include <glm/gtc/type_ptr.hpp>
#include "GLCommon.h"

Text::Text()
{
}

Text::~Text()
{
}

void Text::SetShader(Shader& shader)
{
	m_Shader = &shader;
}

void Text::SetFont(Font& font)
{
	m_Font = &font;

	// Configure VAO/VBO for texture quads
	GLCall(glGenVertexArrays(1, &VAO));
	GLCall(glGenBuffers(1, &VBO));
	GLCall(glBindVertexArray(VAO));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW));
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindVertexArray(0));
}

void Text::SetString(const std::string& text)
{
	m_Text = text;
}

void Text::Render(Shader &shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
{
	// Activate corresponding render state
	shader.Use();
	//glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(800), 0.0f, static_cast<GLfloat>(600));

	//glUniformMatrix4fv(glGetUniformLocation(shader.m_program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	shader.SetVector3f("textColor", color.x, color.y, color.z);
	//glUniform3f(glGetUniformLocation(shader.m_program, "textColor"), color.x, color.y, color.z);
	GLCall(glActiveTexture(GL_TEXTURE0));
	GLCall(glBindVertexArray(VAO));

	// Iterate through all characters
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		auto& ch = m_Font->m_Characters[*c];

		GLfloat xpos = x + ch.Bearing.x * scale;
		//GLfloat ypos = y - (ch.Size.y + ch.Bearing.y) * scale;
		GLfloat ypos = y + (m_Font->m_Characters['H'].Bearing.y - ch.Bearing.y) * scale;

		GLfloat w = ch.Size.x * scale;
		GLfloat h = ch.Size.y * scale;
		// Update VBO for each character
		GLfloat vertices[6][4] = {
			{ xpos,     ypos + h,   0.0, 1.0 },
			{ xpos + w, ypos,       1.0, 0.0 },
			{ xpos,     ypos,       0.0, 0.0 },

			{ xpos,     ypos + h,   0.0, 1.0 },
			{ xpos + w, ypos + h,   1.0, 1.0 },
			{ xpos + w, ypos,       1.0, 0.0 }
		};
		// Render glyph texture over quad
		GLCall(glBindTexture(GL_TEXTURE_2D, ch.TextureID));
		// Update content of VBO memory
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));
		GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices)); // Be sure to use glBufferSubData and not glBufferData

		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
		// Render quad
		GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));
		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
	}
	GLCall(glBindVertexArray(0));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
