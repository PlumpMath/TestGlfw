#include "GameObject.h"


GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture& texture, glm::vec3 color, glm::vec2 velocity)
	:m_Position(pos), m_Size(size), m_Velocity(velocity), m_Color(color), m_Texture(&texture)
{
}

void GameObject::Draw(SpriteRenderer& renderer)
{
	renderer.DrawSprite(*m_Texture, m_Position, m_Size, m_Rotation, m_Color);
}

GameObject::~GameObject()
{
}
