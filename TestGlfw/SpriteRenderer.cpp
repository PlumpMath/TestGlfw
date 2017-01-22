#include "SpriteRenderer.h"
#include <glm/gtc/matrix_transform.inl>
#include "GLCommon.h"


SpriteRenderer::SpriteRenderer(Shader &shader)
	:shader(&shader)
{
	InitRenderData();
}


SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::SetSrcRect(const Rect& srcRect, Texture& texture)
{
	float width = static_cast<float>(texture.m_width);
	float height = static_cast<float>(texture.m_height);

	float ux = srcRect.x / width;
	float uy = srcRect.y / height;
	float uw = (srcRect.x + srcRect.w) / width;
	float uh = (srcRect.y + srcRect.h) / height;

	GLfloat vertices[] = {
		// Pos										// Tex
		0.0f, srcRect.h / height,					ux, uh, // bottom left
		srcRect.w / width, 0.0f,					uw, uy, // top right
		0.0f, 0.0f,									ux, uy, // top left

		0.0f, srcRect.h / height,					ux, uh, // bottom left
		srcRect.w / width, srcRect.h / height,		uw, uh, // bottom right
		srcRect.w / width, 0.0f,					uw, uy // top right
	};

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));
	GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindVertexArray(0));
}

void SpriteRenderer::DrawSprite(Texture& texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color)
{
	shader->Use();
	glm::mat4 model(1.f);
	model = glm::translate(model, glm::vec3(position, 0.0f));
	
	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
	model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

	model = glm::scale(model, glm::vec3(size, 1.0f));

	shader->SetMatrix4("model", model);
	shader->SetVector3f("spriteColor", color);

	GLCall(glActiveTexture(GL_TEXTURE0));
	texture.Bind();

	GLCall(glBindVertexArray(VAO));
	GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));
	GLCall(glBindVertexArray(0));
}

void SpriteRenderer::InitRenderData()
{
	GLfloat vertices[] = {
		// Pos      // Tex
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	GLCall(glGenVertexArrays(1, &VAO));
	GLCall(glGenBuffers(1, &VBO));

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

	GLCall(glBindVertexArray(VAO));
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindVertexArray(0));
}
