#include "Gravity.h"


Gravity::Gravity(void)
{
	gPower = 0.0f;
}

Gravity::~Gravity()
{
}

void Gravity::PutGravityOnActor(Vector2 & pos)
{
	// 重力加算
	gPower += GRAVITY;
	// 物体のﾎﾟｼﾞｼｮﾝ事態に重力をかける
	pos.y += gPower;
}
