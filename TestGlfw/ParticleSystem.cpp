#include "ParticleSystem.h"
#include "AssetManager.h"
#include <glm/gtc/matrix_transform.inl>


ParticleSystem::ParticleSystem()
{
}

ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::Init(Texture& texture, int amount)
{
	this->texture = &texture;
	m_InitialAmount = amount;

	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(800), static_cast<GLfloat>(600), 0.0f, -1.0f, 1.0f);
	shader = &AssetManager::LoadShader("particle.vert", "particle.frag", "particle");
	shader->Use();
	shader->SetInteger("sprite", 0);
	shader->SetMatrix4("projection", projection);

	GLuint VBO;
	GLfloat particle_quad[] = {
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(this->VAO);
	// Fill mesh buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(particle_quad), particle_quad, GL_STATIC_DRAW);
	// Set mesh attributes
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glBindVertexArray(0);

	m_Particles.reserve(m_MaxParticles);
	for(auto i = 0; i < m_MaxParticles; ++i)
	{
		m_Particles.push_back(Particle());
	}
}

void ParticleSystem::Update(float delta, GameObject &object, int newParticles, glm::vec2 offset)
{
	for(auto i = 0; i < m_NewParticlesPerUpdate; ++i)
	{
		auto unusedParticle = FirstUnusedParticle();
		RespawnParticle(m_Particles[unusedParticle], object, offset);
	}

	for(auto i = 0; i < m_InitialAmount; ++i)
	{
		auto& p = m_Particles[i];
		p.Life -= delta;
		if(p.Life > 0.f)
		{
			p.Position -= p.Velocity * delta;
			p.Color.a -= delta * 2.5f;
		}
	}
}

int ParticleSystem::FirstUnusedParticle()
{
	// Search from last used particle, this will usually return almost instantly
	for (auto i = m_LastUsedParticle; i < m_NewParticlesPerUpdate; ++i) {
		if (m_Particles[i].Life <= 0.0f) {
			m_LastUsedParticle = i;
			return i;
		}
	}
	// Otherwise, do a linear search
	for (auto i = 0; i < m_LastUsedParticle; ++i) {
		if (m_Particles[i].Life <= 0.0f) {
			m_LastUsedParticle = i;
			return i;
		}
	}
	// Override first particle if all others are alive
	m_LastUsedParticle = 0;
	return 0;
}

void ParticleSystem::RespawnParticle(Particle& particle, GameObject& object, glm::vec2 offset)
{
	GLfloat random = ((rand() % 100) - 50) / 10.0f;
	GLfloat rColor = 0.5f + ((rand() % 100) / 100.0f);
	particle.Position = object.m_Position + random + offset;
	particle.Color = glm::vec4(rColor, rColor, rColor, 1.0f);
	particle.Life = 1.0f;
	particle.Velocity = object.m_Velocity * 0.1f;
}

void ParticleSystem::Render()
{
	// Use additive blending to give it a 'glow' effect
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	shader->Use();
	for (Particle particle : m_Particles)
	{
		if (particle.Life > 0.0f)
		{
			shader->SetVector2f("offset", particle.Position);
			shader->SetVector4f("color", particle.Color);
			texture->Bind();
			glBindVertexArray(this->VAO);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindVertexArray(0);
		}
	}
	// Don't forget to reset to default blending mode
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
