#pragma once
#include "IGame.h"
#include "Texture.h"

class LoadSpeedTest : public IGame
{
public:
	~LoadSpeedTest() override;
	void Init() override;
	void ProcessInput(float delta, double mouse_x, double mouse_y) override;
	void Update(float delta) override;
	void Render() override;

	Texture* tex;
};
