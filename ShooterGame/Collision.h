#pragma once
#include <math.h>
#include "Geometory.h"

// �~�`�����蔻��p�֐���޼ު��
struct CircleCollision
{
	bool operator()(const Vector2I& distance,const Vector2I& size,int zdiff)
	{
		// z���̍���5�ȉ���
		if (abs(zdiff) <= 5)
		{
			// �������Ă�����
			if (abs(distance.x) <= (size.x / 2) &&
				abs(distance.y) <= (size.y / 2))
			{
				return true;
			}
		}
		return false;
	}
};

struct BoxOutCollision
{
	bool operator()(const Vector2I& target, const Vector2I& first, const Vector2I& size)
	{
		// �������Ă�����
		if (target.x <= first.x || target.y <= first.y||target.x > first.x + size.x||target.y > first.y + size.y)
		{
			return true;
		}
		return false;
	}
};