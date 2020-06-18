#pragma once

#include "Vector2.h"

class Camera
{
public:
	Camera(Vector2 pos);
	~Camera();

	void UpDate(const Vector2& pos);
	// you can get camera's position
	Vector2& GetPos(void)
	{
		return pos;
	}

private:
	Vector2 pos;
	Vector2 fixedPos;
};

