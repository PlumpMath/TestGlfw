#pragma once

class Rect
{
public:
	Rect() = default;
	Rect(float x, float y, float w, float h)
		:x(x), y(y), w(w), h(h)
	{
		
	}
	~Rect() = default;

	float x = 0, y = 0, w = 0, h = 0;
};

