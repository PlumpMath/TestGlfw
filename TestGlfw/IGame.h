#pragma once
class IGame
{
public:
	IGame() = default;
	virtual ~IGame(){};

	virtual void Init() = 0;
	virtual void ProcessInput(float delta, double mouse_x, double mouse_y) = 0;
	virtual void Update(float delta) = 0;
	virtual void Render() = 0;
};

