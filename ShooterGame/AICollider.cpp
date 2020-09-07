#include <DxLib.h>
#include "AICollider.h"
#include "Enemy.h"

AICollider::AICollider()
{
	pos_ = { 0,0 };
	z_ = 0;
}

AICollider::~AICollider()
{
}

void AICollider::SetPos(const Vector2I& pos,const int& z)
{
	pos_ = pos;
	z_ = z;
}

void AICollider::Draw(void)
{
	DrawBox(pos_.x - (size / 2),pos_.y + (z_/2) - (size / 2),
		pos_.x + (size / 2), pos_.y + (z_ / 2) + (size / 2),
		0xff0000, false);
}
