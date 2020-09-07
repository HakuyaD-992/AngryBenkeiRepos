#pragma once
#include <math.h>
#include "Geometory.h"

// 円形当たり判定用関数ｵﾌﾞｼﾞｪｸﾄ
struct CircleCollision
{
	bool operator()(const Vector2I& distance,const Vector2I& size,int zdiff)
	{
		// z軸の差が5以下で
		if (abs(zdiff) <= 5)
		{
			// 当たっていたら
			if (abs(distance.x) <= (size.x / 2) &&
				abs(distance.y) <= (size.y / 2))
			{
				return true;
			}
		}
		return false;
	}
};