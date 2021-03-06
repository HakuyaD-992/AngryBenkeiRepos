#pragma once
#include <math.h>
#include "Geometory.h"
#include "ActorType.h"

// 円形当たり判定用関数ｵﾌﾞｼﾞｪｸﾄ
struct CircleCollision
{
	bool operator()(const ActorType& type,const Vector2I& distance,const Vector2I& size,int zdiff)
	{
		if (type != ActorType::Bigboy)
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
		}
		else
		{
			// z軸の差が50以下で
			if (abs(zdiff) <= 50)
			{
				// 当たっていたら
				if (abs(distance.x) <= (size.x / 2)-50 &&
					abs(distance.y) <= (size.y / 2))
				{
					return true;
				}
			}
		}
		return false;
	}
};

struct BoxOutCollision
{
	bool operator()(const Vector2I& target, const Vector2I& first, const Vector2I& size)
	{
		// 当たっていたら
		if (target.x <= first.x || target.y <= first.y||target.x > first.x + size.x||target.y > first.y + size.y)
		{
			return true;
		}
		return false;
	}
};

struct BoxCollision
{
	bool operator()(const Vector2I& pos1, const Vector2I& pos2, const Vector2I& size1, const Vector2I& size2,const int& zdiff)
	{
		if (abs(zdiff) <= 50)
		{
			if ((pos1.y + (size1.y/2) >= pos2.y) || (pos1.y <= pos2.y + size2.y))
			{
				return true;
			}
		}
		return false;
	}
};