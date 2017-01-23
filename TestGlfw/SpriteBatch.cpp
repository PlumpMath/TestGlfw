#include "SpriteBatch.h"
#include "GLCommon.h"
#include "Shader.h"
#include "Texture.h"
#include "math.h"
#include "Rect.h"

SpriteBatch::SpriteBatch(int screenW, int screenH, Shader* shader)
	:m_Shader(shader), screenW(screenW), screenH(screenH)
{
	GLfloat vertices[] = {
		// Pos      // Tex				// Color
		0.0f, 164.f,	0.0f, 1.0f,		1.f, 1.f, 1.f, 1.f,
		164.f, 0.0f,	1.0f, 0.0f,		1.f, 1.f, 1.f, 1.f,
		0.0f, 0.0f,		0.0f, 0.0f,		1.f, 1.f, 1.f, 1.f,

		0.0f, 164.f,	0.0f, 1.0f,		1.f, 1.f, 1.f, 1.f,
		164.f, 164.f,	1.0f, 1.0f,		1.f, 1.f, 1.f, 1.f,
		164.f, 0.0f,	1.0f, 0.0f,		1.f, 1.f, 1.f, 1.f,
	};

	GLCall(glGenVertexArrays(1, &VAO));
	GLCall(glGenBuffers(1, &VBO));

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

	GLCall(glBindVertexArray(VAO));
	GLCall(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0));
	GLCall(glEnableVertexAttribArray(0));

	GLCall(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(4 * sizeof(GLfloat))));
	GLCall(glEnableVertexAttribArray(1));

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindVertexArray(0));
}

SpriteBatch::~SpriteBatch()
{
}

void SpriteBatch::Begin()
{
	m_DidBegin = true;
}

void SpriteBatch::End()
{
	Flush();
	m_DidBegin = false;
}

void SpriteBatch::Flush()
{
}

void SpriteBatch::Draw(Texture* texture, glm::vec2 position, glm::vec3 color)
{
	float w = static_cast<float>(texture->m_width);
	float h = static_cast<float>(texture->m_height);
	float x = position.x;
	float y = position.y;

	GLfloat vertices[] = {
		// Pos				// Tex			// Color
		x, y + h,		0.0f, 1.0f,		1.f, 1.f, 1.f, 1.f,
		x + w, y,		1.0f, 0.0f,		1.f, 1.f, 1.f, 1.f,
		x, y,			0.0f, 0.0f,		1.f, 1.f, 1.f, 1.f,

		x, y + h,		0.0f, 1.0f,		1.f, 1.f, 1.f, 1.f,
		x + w, h,		1.0f, 1.0f,		1.f, 1.f, 1.f, 1.f,
		x + w, y,		1.0f, 0.0f,		1.f, 1.f, 1.f, 1.f
	};

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));
	GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

	m_Shader->Use();

	//m_Shader->SetVector3f("spriteColor", color);

	GLCall(glActiveTexture(GL_TEXTURE0));
	texture->Bind();

	GLCall(glBindVertexArray(VAO));
	GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));
	GLCall(glBindVertexArray(0));
}

/*void SpriteBatch::Draw(Texture* texture, const Rect& srcRect, glm::vec2 position, glm::vec2 scale,
	float rotate, glm::vec3 color, glm::vec2 origin)
{
	m_Shader->Use();

	//m_Shader->SetVector3f("spriteColor", color);

	GLCall(glActiveTexture(GL_TEXTURE0));
	texture->Bind();

	GLCall(glBindVertexArray(VAO));
	GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));
	GLCall(glBindVertexArray(0));
}*/

void SpriteBatch::Draw(Texture* texture, const Rect& srcRect, glm::vec2 position, glm::vec2 scale,
	float rotate, glm::vec4 c, glm::vec2 origin)
{
	const float worldOriginX = position.x + origin.x;
	const float worldOriginY = position.y + origin.y;
	float fx = -origin.x;
	float fy = -origin.y;
	//float fx2 = texture->m_width - origin.x;
	//float fy2 = texture->m_height - origin.y;
	float fx2 = srcRect.w - origin.x;
	float fy2 = srcRect.h - origin.y;

	if(scale.x != 1.f || scale.y != 1.f)
	{
		fx *= scale.x;
		fy *= scale.y;
		fx2 *= scale.x;
		fy2 *= scale.y;
	}

	const float p1x = fx;
	const float p1y = fy;
	const float p2x = fx;
	const float p2y = fy2;
	const float p3x = fx2;
	const float p3y = fy2;
	const float p4x = fx2;
	const float p4y = fy;

	float x1;
	float y1;
	float x2;
	float y2;
	float x3;
	float y3;
	float x4;
	float y4;

	if (rotate != 0) {
		// TODO: Replace with faster transcendental table
		const float cosVal = cos(rotate * PiOver180);//MathUtils.cosDeg(rotation);
		const float sinVal = sin(rotate * PiOver180);//MathUtils.sinDeg(rotation);

		x1 = cosVal * p1x - sinVal * p1y;
		y1 = sinVal * p1x + cosVal * p1y;

		x2 = cosVal * p2x - sinVal * p2y;
		y2 = sinVal * p2x + cosVal * p2y;

		x3 = cosVal * p3x - sinVal * p3y;
		y3 = sinVal * p3x + cosVal * p3y;

		x4 = x1 + (x3 - x2);
		y4 = y3 - (y2 - y1);
	}
	else {
		x1 = p1x;
		y1 = p1y;

		x2 = p2x;
		y2 = p2y;

		x3 = p3x;
		y3 = p3y;

		x4 = p4x;
		y4 = p4y;
	}

	x1 += worldOriginX;
	y1 += worldOriginY;
	x2 += worldOriginX;
	y2 += worldOriginY;
	x3 += worldOriginX;
	y3 += worldOriginY;
	x4 += worldOriginX;
	y4 += worldOriginY;

	float invTexWidth = 1.0f / texture->m_width;
	float invTexHeight = 1.0f / texture->m_height;

	float u = srcRect.x * invTexWidth;
	float v = (srcRect.y + srcRect.h) * invTexHeight;
	float u2 = (srcRect.x + srcRect.w) * invTexWidth;
	float v2 = srcRect.y * invTexHeight;

	float w = static_cast<float>(texture->m_width);
	float h = static_cast<float>(texture->m_height);
	float x = position.x;
	float y = position.y;

	GLfloat vertices[] = {
		// Pos			// Tex			// Color
		x1, y1,			u, v2,			c.r, c.g, c.b, c.a, // bottom left
		x2, y2,			u, v,			c.r, c.g, c.b, c.a, // top right
		x3, y3,			u2, v,			c.r, c.g, c.b, c.a, // top left

		x1, y1,			u, v2,			c.r, c.g, c.b, c.a, // bottom left
		x4, y4,			u2, v2,			c.r, c.g, c.b, c.a, // bottom right
		x3, y3,			u2, v,			c.r, c.g, c.b, c.a // top right
	};

	/*GLfloat vertices[] = {
		// Pos			// Tex			// Color
		x1, y1,			u, v,			1.f, 1.f, 1.f, 1.f, // bottom left
		x2, y2,			u, v2,			1.f, 1.f, 1.f, 1.f, // top right
		x3, y3,			u2, v2,			1.f, 1.f, 1.f, 1.f, // top left

		x1, y1,			u, v,			1.f, 1.f, 1.f, 1.f, // bottom left
		x4, y4,			u2, v,			1.f, 1.f, 1.f, 1.f, // bottom right
		x3, y3,			u2, v2,			1.f, 1.f, 1.f, 1.f // top right
	};*/

	/*GLfloat vertices[] = {
		// Pos				// Tex			// Color
		x, y + h,		0.0f, 1.0f,		1.f, 1.f, 1.f, 1.f, // bottom left
		x + w, y,		1.0f, 0.0f,		1.f, 1.f, 1.f, 1.f, // top right
		x, y,			0.0f, 0.0f,		1.f, 1.f, 1.f, 1.f, // top left

		x, y + h,		0.0f, 1.0f,		1.f, 1.f, 1.f, 1.f, // bottom left
		x + w, y + h,	1.0f, 1.0f,		1.f, 1.f, 1.f, 1.f, // bottom right
		x + w, y,		1.0f, 0.0f,		1.f, 1.f, 1.f, 1.f // top right
	};*/

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));
	GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

	m_Shader->Use();

	//m_Shader->SetVector3f("spriteColor", c);

	GLCall(glActiveTexture(GL_TEXTURE0));
	texture->Bind();

	GLCall(glBindVertexArray(VAO));
	GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));
	GLCall(glBindVertexArray(0));
}
