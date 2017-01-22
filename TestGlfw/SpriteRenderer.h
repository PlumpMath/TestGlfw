#pragma once
#include "Shader.h"
#include "glm/glm.hpp"
#include "Texture.h"
#include "Rect.h"

class SpriteRenderer
{
public:
	SpriteRenderer(Shader &shader);
	~SpriteRenderer();

	void SetSrcRect(const Rect& srcRect, Texture& texture);

	void DrawSprite(Texture &texture, glm::vec2 position,
		glm::vec2 size = glm::vec2(10, 10), float rotate = 0.0f,
		glm::vec3 color = glm::vec3(1.f));

private:
	GLuint VBO, VAO;
	Shader* shader;
	void InitRenderData();
};

