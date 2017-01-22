#include "Breakout.h"
#include "AssetManager.h"
#include <glm/gtc/matrix_transform.inl>
#include "GLCommon.h"


Breakout::Breakout(int width, int height)
	:width(width), height(height)
{
}

Breakout::~Breakout()
{
}

void Breakout::Init()
{
	AssetManager::LoadShader("sprite_renderer.vert", "sprite_renderer.frag", "sprite");
	AssetManager::LoadShader("batch.vert", "batch.frag", "batch");

	auto& spriteShader = AssetManager::GetShader("sprite");

	glm::mat4 projection = glm::ortho(0.f, static_cast<float>(width),
		static_cast<float>(height), 0.f, -1.f, 1.f);

	spriteShader.Use();
	spriteShader.SetInteger("image", 0);
	spriteShader.SetMatrix4("projection", projection);

	m_Renderer = std::make_unique<SpriteRenderer>(spriteShader);
	ace = &AssetManager::LoadTexture("Ace_000.png");
	//m_Renderer->SetSrcRect(Rect(0, 0, 164, 82), *ace);
	//m_Renderer->SetSrcRect(Rect(0, 0, 82, 82), *ace);

	AssetManager::LoadShader("text.vert", "text.frag", "text");
	font.Load("fonts/Certified.ttf", 50);

	text.SetFont(font);
	text.SetShader(AssetManager::GetShader("text"));
	text.SetString("Hello");

	auto& particleTex = AssetManager::LoadTexture("particle.png");
	particles.Init(particleTex, 500);
}

void Breakout::ProcessInput(float delta, double mouse_x, double mouse_y)
{
	gameObj.m_Position = glm::vec2(mouse_x, mouse_y);
}

void Breakout::Update(float delta)
{
	particles.Update(delta, gameObj, 50, glm::vec2(10, 10));
}

void Breakout::Render()
{
	glm::mat4 projection = glm::ortho(0.f, static_cast<float>(width),
		static_cast<float>(height), 0.f, -1.f, 1.f);

	//glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(800), 0.0f, static_cast<GLfloat>(600));

	auto& spriteShader = AssetManager::GetShader("sprite");
	spriteShader.Use();
	spriteShader.SetInteger("image", 0);
	spriteShader.SetMatrix4("projection", projection);

	m_Renderer->DrawSprite(*ace, glm::vec2(200, 200), glm::vec2(300, 400),
		45.0f, glm::vec3(0.0f, 1.0f, 0.0f));

	m_Renderer->DrawSprite(*ace, glm::vec2(0, 0), glm::vec2(300, 400),
		90.f, glm::vec3(1.0f, 1.0f, 1.0f));

	m_Renderer->DrawSprite(*ace, glm::vec2(0, 0), glm::vec2(300, 400),
		0.f, glm::vec3(1.0f, 1.0f, 1.0f));

	m_Renderer->DrawSprite(*ace, glm::vec2(500, 0), glm::vec2(ace->m_width, ace->m_height),
		0.f, glm::vec3(1.0f, 1.0f, 1.0f));

	/*for(auto i = 0; i < 100; ++i)
	{
		for(auto j = 0; j < 100; ++j)
		{
			m_Renderer->DrawSprite(*ace, glm::vec2(i, j), glm::vec2(ace->m_width, ace->m_height),
				0.f, glm::vec3(1.0f, 1.0f, 1.0f));
		}		
	}*/

	auto& textShader = AssetManager::GetShader("text");
	textShader.Use();
	textShader.SetMatrix4("projection", projection);
	text.Render(AssetManager::GetShader("text"), "Hello", 100, 300, 1.f, glm::vec3(1.f));

	//particles.Render();
}
