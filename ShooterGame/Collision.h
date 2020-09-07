#pragma once
#include <math.h>
#include "Geometory.h"

// ‰~Œ`“–‚½‚è”»’è—pŠÖ”µÌŞ¼Şª¸Ä
struct CircleCollision
{
	bool operator()(const Vector2I& distance,const Vector2I& size,int zdiff)
	{
		// z²‚Ì·‚ª5ˆÈ‰º‚Å
		if (abs(zdiff) <= 5)
		{
			// “–‚½‚Á‚Ä‚¢‚½‚ç
			if (abs(distance.x) <= (size.x / 2) &&
				abs(distance.y) <= (size.y / 2))
			{
				return true;
			}
		}
		return false;
	}
};
