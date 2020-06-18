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
	// d—Í‰ÁZ
	gPower += GRAVITY;
	// •¨‘Ì‚ÌÎß¼Ş¼®İ–‘Ô‚Éd—Í‚ğ‚©‚¯‚é
	pos.y += gPower;
}
