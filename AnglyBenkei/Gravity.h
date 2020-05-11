#pragma once
#include <mutex>
#include "Vector2.h"

// かかる一定重力
#define GRAVITY 0.3f

class Gravity
{
public:
	Gravity(void);
	~Gravity();

	// 物体に対して重力をかける関数
	void PutGravityOnActor(Vector2& pos);

private:
	// 物体に対してかかる重力
	float gPower;
};

