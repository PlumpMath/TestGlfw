#pragma once

#include <vector>

#include <glm/glm.hpp>
#include "GameObject.h"
#include "Shader.h"

class ParticleSystem
{
public:
	struct Particle
	{
		glm::vec2 Position, Velocity;
		glm::vec4 Color;
		float Life;

		Particle()
			:Position(0.f), Velocity(30.f), Color(1.f), Life(2.f){}
	};

	ParticleSystem();
	~ParticleSystem();
	void Init(Texture& texture, int amount);
	void Update(float delta, GameObject &obj, int newParticles, glm::vec2 offset);
	int FirstUnusedParticle();
	void RespawnParticle(Particle &particle, GameObject &object, glm::vec2 offset);
	void Render();

	GLuint VAO;

	Shader* shader;
	Texture *texture;
	int m_InitialAmount;

	const int m_MaxParticles = 500;
	const int m_NewParticlesPerUpdate = 2;
	int m_LastUsedParticle = 0;

	std::vector<Particle> m_Particles;
};

