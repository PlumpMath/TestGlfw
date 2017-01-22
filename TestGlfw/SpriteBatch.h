#pragma once

#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

class Rect;
class Shader;
class Texture;

class SpriteBatch
{
public:

	struct Vertex
	{
		float pos[2] = {0.f, 0.f};
		float uv[2] = { 0.f, 0.f };
		float color[4] =  { 1.f, 1.f, 1.f, 1.f };
		Vertex(float x, float y, float ux, float uy, float c1, float c2, float c3, float c4)
		{
			pos[0] = x;
			pos[1] = y;
			uv[0] = ux;
			uv[1] = uy;
			color[0] = c1;
			color[1] = c2;
			color[2] = c3;
			color[3] = c4;
		}
	};

	SpriteBatch(int screenW, int screenH, Shader* shader);
	~SpriteBatch();

	void Begin();
	void End();
	void Flush();
	void Draw(Texture* texture, glm::vec2 position, glm::vec3 color = glm::vec3(1.f));
	void Draw(Texture* texture, const Rect& srcRect, glm::vec2 position, glm::vec2 scale, 
		float rotate, glm::vec3 color, glm::vec2 origin);

	GLuint VAO, VBO;

private:
	Shader* m_Shader;
	std::vector<float> m_Verts;
	int screenW = 0;
	int screenH = 0;
	bool m_DidBegin;
	GLuint m_TextureIndex = 0;
};

