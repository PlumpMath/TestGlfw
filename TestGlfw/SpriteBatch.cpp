#include "SpriteBatch.h"
#include "GLCommon.h"
#include "Shader.h"
#include "Texture.h"

SpriteBatch::SpriteBatch(int screenW, int screenH, Shader* shader)
	:m_Shader(shader), screenW(screenW), screenH(screenH)
{
	GLfloat vertices[] = {
		// Pos      // Tex				// Color
		0.0f, 164.f,	0.0f, 1.0f,		1.f, 1.f, 1.f, 1.f,
		164.f, 0.0f,	1.0f, 0.0f,		1.f, 1.f, 1.f, 1.f,
		0.0f, 0.0f,		0.0f, 0.0f,		1.f, 1.f, 1.f, 1.f,

		0.0f, 164.f,	0.0f, 1.0f,		1.f, 1.f, 1.f, 1.f,
		164.f, 164.f,	1.0f, 1.0f,		1.f, 1.f, 1.f, 1.f,
		164.f, 0.0f,	1.0f, 0.0f,		1.f, 1.f, 1.f, 1.f,
	};

	GLCall(glGenVertexArrays(1, &VAO));
	GLCall(glGenBuffers(1, &VBO));

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

	GLCall(glBindVertexArray(VAO));
	GLCall(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0));
	GLCall(glEnableVertexAttribArray(0));

	GLCall(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(4 * sizeof(GLfloat))));
	GLCall(glEnableVertexAttribArray(1));

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindVertexArray(0));
}

SpriteBatch::~SpriteBatch()
{
}

void SpriteBatch::Begin()
{
	m_DidBegin = true;
}

void SpriteBatch::End()
{
	Flush();
	m_DidBegin = false;
}

void SpriteBatch::Flush()
{
}

void SpriteBatch::Draw(Texture* texture, glm::vec2 position, glm::vec3 color)
{
	float w = texture->m_width;
	float h = texture->m_height;
	float x = position.x;
	float y = position.y;

	GLfloat vertices[] = {
		// Pos				// Tex			// Color
		x, y + h,		0.0f, 1.0f,		1.f, 1.f, 1.f, 1.f,
		x + w, y,		1.0f, 0.0f,		1.f, 1.f, 1.f, 1.f,
		x, y,			0.0f, 0.0f,		1.f, 1.f, 1.f, 1.f,

		x, y + h,		0.0f, 1.0f,		1.f, 1.f, 1.f, 1.f,
		x + w, h,		1.0f, 1.0f,		1.f, 1.f, 1.f, 1.f,
		x + w, y,		1.0f, 0.0f,		1.f, 1.f, 1.f, 1.f
	};

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));
	GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

	m_Shader->Use();

	m_Shader->SetVector3f("spriteColor", color);

	GLCall(glActiveTexture(GL_TEXTURE0));
	texture->Bind();

	GLCall(glBindVertexArray(VAO));
	GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));
	GLCall(glBindVertexArray(0));
}

void SpriteBatch::Draw(Texture* texture, const Rect& srcRect, glm::vec2 position, glm::vec2 scale,
	float rotate, glm::vec3 color, glm::vec2 origin)
{
	m_Shader->Use();

	//m_Shader->SetVector3f("spriteColor", color);

	GLCall(glActiveTexture(GL_TEXTURE0));
	texture->Bind();

	GLCall(glBindVertexArray(VAO));
	GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));
	GLCall(glBindVertexArray(0));
}
