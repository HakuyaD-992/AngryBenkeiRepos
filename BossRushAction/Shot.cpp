#include <DxLib.h>

#include "SpriteManager.h"
#include "Shot.h"



Shot::Shot(Vector2 pos,DIRECTION direction)
{
	this->pos = pos;
	size = Vector2(Size_X, Size_Y);
	firstSpeed = AccelFirstSpeed;
	accelSpeed = 0.0f;
	accel = 0.0f;
	animCount = 0;
	this->direction = direction;
	deleteFlag = false;

	Init();
}


Shot::~Shot()
{
}

void Shot::Action(void)
{
	accel += 0.3;
	firstSpeed = accel;
	accelSpeed = firstSpeed;

	switch (direction)
	{
	case Direction_Right:
		pos.x += accelSpeed;
		break;
	case Direction_Left:
		pos.x -= accelSpeed;
		break;
	default:
		break;
	}

}

bool Shot::Init(void)
{
	lpSpriteMng.GetID("Image/GamePlay/Player/AttackShot/shot.png", Vector2(68, 9), Vector2(10, 6));
	return true;
}

void Shot::Draw(void)
{
	animCount++;
	if (animCount <= 59)
	{
		if (direction == Direction_Right)
		{
			DrawRotaGraph(pos.x, pos.y, 1.0f, 0.0f, lpSpriteMng.GetID("Image/GamePlay/Player/AttackShot/shot.png")[animCount], true, true);
		}
		else
		{
			DrawRotaGraph(pos.x, pos.y, 1.0f, 0.0f, lpSpriteMng.GetID("Image/GamePlay/Player/AttackShot/shot.png")[animCount], true, false);
		}
	}
	else
	{
		animCount = 0;
	}
}
