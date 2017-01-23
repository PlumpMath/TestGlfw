#pragma once
#include "IGame.h"

class LoadDDSTest : public IGame
{
public:
	LoadDDSTest();
	~LoadDDSTest();
	void Init() override;
	void ProcessInput(float delta, double mouse_x, double mouse_y) override;
	void Update(float delta) override;
	void Render() override;
};

