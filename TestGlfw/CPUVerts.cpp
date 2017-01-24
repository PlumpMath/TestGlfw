#include "CPUVerts.h"
#include "AssetManager.h"
#include <glm/gtc/matrix_transform.inl>
#include "Rect.h"
#include <cstdlib>
#include <ctime>

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
	AssetManager::LoadShader("TransformVertexShader.vertexshader", "TextureFragmentShader.fragmentshader", "dunno");
	auto& shader = AssetManager::GetShader("batch");
	//auto& shader = AssetManager::GetShader("dunno");

	glm::mat4 projection = glm::ortho(0.f, static_cast<float>(width),
		static_cast<float>(height), 0.f, -1.f, 1.f);

	shader.Use();
	shader.SetInteger("image", 0);
	shader.SetMatrix4("projection", projection);

	//ace = AssetManager::LoadTexture("Ace_000.png");
	ace = AssetManager::LoadTexture("fsScreenLoopBG_042.dds");
	//ace = AssetManager::LoadTexture("Mipster-splash_PNG_DXT5.dds");

	m_Batch = std::make_unique<SpriteBatch>(width, height, &shader);
}

void CPUVerts::ProcessInput(float delta, double mouse_x, double mouse_y)
{
}

void CPUVerts::Update(float delta)
{
}

float rand(float min, float max)
{
	srand(static_cast<unsigned>(time(nullptr)));
	return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
}

float randZeroToX(float x)
{
	return static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / x));
}

float randZeroToOne()
{
	return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);;
}

void CPUVerts::Render()
{
	m_Batch->Begin();
	m_Batch->Draw(ace, Rect(0, 0, 1024, 768), glm::vec2(0.f), glm::vec2(1.f), 0.f,
		glm::vec4(1.f), glm::vec2(0,0));
	
	static float rot = 0.f;
	rot += 0.1f;

	/*m_Batch->Draw(ace, Rect(0, 0, 162, 162), glm::vec2(0, 0), glm::vec2(1.f, 1.f), rot,
		glm::vec4(1.f), glm::vec2(0 + ace->m_width /2 ,  0 + ace->m_height / 2));

	glm::vec2 pos(200.f, 300.f);
	glm::vec2 scale(sin(rot*0.01f), sin(rot*0.01f));
	m_Batch->Draw(ace, Rect(0, 0, 162, 162), pos, scale, rot,
		glm::vec4(1.f), glm::vec2(ace->m_width / 2, ace->m_height / 2));*/

	/*m_Batch->Draw(ace, Rect(0, 0, 162, 162), glm::vec2(300.f, 0.f), glm::vec2(1.f, 1.f), 0.f,
		glm::vec4(1.f), glm::vec2(ace->m_width / 2, ace->m_height / 2));*/

	/*m_Batch->Draw(ace, Rect(0, 0, 81, 81), glm::vec2(200.f, 200.f), glm::vec2(1.f, 1.f), rot,
		glm::vec4(1.f), glm::vec2(ace->m_width/2, ace->m_height/2));*/


	/*for(auto i = 0; i < 1000; i += 5)
	{
		auto randomPos = glm::vec2(randZeroToX(600.f), randZeroToX(400.f));
		auto zeroToOne = randZeroToOne();
		auto randomColor = glm::vec4(randZeroToOne(), randZeroToOne(), randZeroToOne(), 1.f);
		m_Batch->Draw(ace, Rect(0, 0, 162, 162), 
			randomPos,
			glm::vec2(1.f, 1.f), 
			sin(rot) * 5,
			randomColor, 
			glm::vec2( ace->m_width / 2, ace->m_height / 2));
	}*/

	//m_Batch->Draw(ace, glm::vec2(0, 0));
	m_Batch->End();
}
