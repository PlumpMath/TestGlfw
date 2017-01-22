#include "CPUVerts.h"
#include "AssetManager.h"
#include <glm/gtc/matrix_transform.inl>
#include "Rect.h"

CPUVerts::CPUVerts(int width, int height)
	:width(width), height(height)
{
}

CPUVerts::~CPUVerts()
{
}

void CPUVerts::Init()
{
	AssetManager::LoadShader("batch.vert", "batch.frag", "batch");
	auto& shader = AssetManager::GetShader("batch");

	glm::mat4 projection = glm::ortho(0.f, static_cast<float>(width),
		static_cast<float>(height), 0.f, -1.f, 1.f);

	shader.Use();
	shader.SetInteger("image", 0);
	shader.SetMatrix4("projection", projection);

	ace = &AssetManager::LoadTexture("Ace_000.png");

	m_Batch = std::make_unique<SpriteBatch>(width, height, &shader);
}

void CPUVerts::ProcessInput(float delta, double mouse_x, double mouse_y)
{
}

void CPUVerts::Update(float delta)
{
}

void CPUVerts::Render()
{
	m_Batch->Begin();
	m_Batch->Draw(ace, Rect(0, 0, 162, 162), glm::vec2(0, 0), glm::vec2(162, 162), 0.f,
		glm::vec3(1.f, 1.f, 1.f), glm::vec2(0,0));
	
	for(auto i = 0; i < 1000; i += 5)
	{
		m_Batch->Draw(ace, glm::vec2(i, 0.f));
		/*m_Batch->Draw(ace, Rect(0, 0, 162, 162), glm::vec2(i, 0), glm::vec2(162, 162), 0.f,
			glm::vec3(1.f, 1.f, 1.f), glm::vec2(0, 0));*/
	}

	//m_Batch->Draw(ace, glm::vec2(0, 0));
	m_Batch->End();
}
