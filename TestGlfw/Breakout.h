#pragma once

#include "SpriteRenderer.h"
#include "Texture.h"
#include <memory>
#include "Font.h"
#include "Text.h"
#include "ParticleSystem.h"
#include "GameObject.h"
#include "IGame.h"

class Breakout : public IGame
{
public:

	Breakout(int width, int height);
	~Breakout() override;

	void Init() override;
	void ProcessInput(float delta, double mouse_x, double mouse_y) override;
	void Update(float delta) override;
	void Render() override;

	std::unique_ptr<SpriteRenderer> m_Renderer;
	Texture* ace;
	GameObject gameObj;
	ParticleSystem particles;

	Font font;
	Text text;

private:
	int width, height;
};

