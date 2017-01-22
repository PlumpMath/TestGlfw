#pragma once
#include "IGame.h"
#include "Texture.h"
#include "SpriteBatch.h"
#include <memory>

class CPUVerts : public IGame
{
public:
	CPUVerts(int width, int height);
	~CPUVerts();

	void Init() override;
	void ProcessInput(float delta, double mouse_x, double mouse_y) override;
	void Update(float delta) override;
	void Render() override;	

private:
	int width, height;
	Texture* ace;
	std::unique_ptr<SpriteBatch> m_Batch;
};

