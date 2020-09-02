#include "Gravity.h"

Gravity::Gravity()
{
	gSpeed_ = 0.0f;
}

Gravity::~Gravity()
{
}

void Gravity::Apply(Vector2I& pos)
{
	if (pos.y <= 500)
	{
		gSpeed_ += g_;
	}
	else
	{
		gSpeed_ = 0.0f;
	}
	pos.y += (int)gSpeed_;
}