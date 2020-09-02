#pragma once
// èdóÕ
#include "Geometory.h"

constexpr float g_ = 0.3f;

class Gravity
{
public:
	Gravity();
	~Gravity();
	void Apply(Vector2I& pos);
private:

	float gSpeed_;
};

