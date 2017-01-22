#pragma once

#include <glm/glm.hpp>

#include "Texture.h"
#include "SpriteRenderer.h"

class GameObject
{
public:
	GameObject() = default;
	GameObject(glm::vec2 pos, glm::vec2 size, Texture& texture, glm::vec3 color = glm::vec3(1.0f),
		glm::vec2 velocity = glm::vec2(0.f, 0.f));
	virtual ~GameObject();
	virtual void Draw(SpriteRenderer& renderer);

	glm::vec2 m_Position = glm::vec2(0.f);
	glm::vec2 m_Size = glm::vec2(0.f); 
	glm::vec2 m_Velocity = glm::vec2(0.f);
	glm::vec2 m_Origin = glm::vec2(0.f);
	glm::vec3 m_Color = glm::vec3(1.f);
	float m_Rotation;
	bool m_IsSolid;
	bool m_IsDestroyed;
	Texture* m_Texture;
};

