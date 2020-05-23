#include <DxLib.h>

#include "BaseEnemy.h"
#include "SpriteManager.h"


BaseEnemy::BaseEnemy()
{
	gravity = new Gravity();

	onFloor = false;

	isJump = false;
	startingJumpForce = -10.0f;

	attackFlag = false;
	intoSightRangeFlag = false;
	sightRange = SightRange;

}


BaseEnemy::~BaseEnemy()
{
}

void BaseEnemy::UpDate(WeakPlayerList playerList)
{
	if (!isJump && !onFloor)
	{
		// put gravity on enemy
		gravity->PutGravityOnActor(pos);
	}
	Action(playerList);
}

void BaseEnemy::Draw(void)
{
	if (enemySpriteName[type][myAnimationType].size() - 1 == 0)
	{
		return;
	}

	float animationID = 0.0f;
	animationCount++;
	if (animationTable[type].find(animationName) != animationTable[type].end())
	{

		count = (animationCount / animationTable[type][animationName][Animation_TB_Interval]);

		if (animationTable[type][animationName][Animation_TB_Loop] ||
			count < animationTable[type][animationName][Animation_TB_Frame])
		{
			count %= animationTable[type][animationName][Animation_TB_Frame];
		}
		else
		{
			count = animationTable[type][animationName][Animation_TB_Frame] - 1;
		}

		animationID = animationTable[type][animationName][Animation_TB_Start] + count;
	}
	if (animationID < enemySpriteName[type][myAnimationType].size())
	{
		switch (direction)
		{
		case Direction_Right:
			DrawRotaGraph(pos.x, pos.y, 1.0f, 0.0f,
				lpSpriteMng.GetEnemyID(enemySpriteName[type], myAnimationType)[animationID],
				true, true);
			break;

		case Direction_Left:
			DrawRotaGraph(pos.x, pos.y, 1.0f, 0.0f,
				lpSpriteMng.GetEnemyID(enemySpriteName[type], myAnimationType)[animationID],
				true, false);
			break;
		default:
			break;
		}
	}
	DrawFormatString(pos.x, pos.y - 100, 0xffffff, "myAnimationType:%d", myAnimationType);
	DrawFormatString(pos.x, pos.y - 50, 0xffffff, "animationID:%f",animationID);

}

bool BaseEnemy::AddAnimation(std::string animName, int frame, int interval, bool loop,ENEMYTYPE eType)
{
	animationTable[eType][animName][Animation_TB_Frame] = frame;
	animationTable[eType][animName][Animation_TB_Interval] = interval;
	animationTable[eType][animName][Animation_TB_Loop] = loop;
	animationTable[eType][animName][Animation_TB_Start] = Animation_TB_Start;
	return true;
}

bool BaseEnemy::SetAnimation(std::string animName,ENEMYTYPE eType)
{
	if (BaseEnemy::animationName == animName)
	{
		return true;
	}
	if (animationTable[eType].find(animName) == animationTable[eType].end())
	{
		return false;
	}
	BaseEnemy::animationName = animName;
	BaseEnemy::animationCount = 0;
	return false;
}

bool BaseEnemy::Init(EnemySprite enemySpriteName)
{
	this->enemySpriteName = enemySpriteName;
	return true;
}

void BaseEnemy::DistanceCalcurator(Vector2 playerPos)
{
	// calcurate distance
	distance = playerPos - pos;

}

bool BaseEnemy::IsFindPlayer(void)
{
	ClampDistance(distance);
	if (!attackFlag)
	{
		if (distance.x <= SightRange && distance.y <= SightRange)
		{
			intoSightRangeFlag = true;
		}
		else
		{
			intoSightRangeFlag = false;
		}
	}

	return intoSightRangeFlag;
}

bool BaseEnemy::IsAttack(void)
{
	// if player is into sight range....
	if(distance.x <= AttackRange)
	{
		attackFlag = true;
		intoSightRangeFlag = false;
	}
	// else player is not into sight range....
	else
	{
		attackFlag = false;
	}
	return attackFlag;
}

void BaseEnemy::ClampDistance(Vector2& val)
{
	// if minus.....
	if (val.x < 0)
	{
		val.x = val.x * -1;
	}
	// if plus....
	else
	{
		val.x = val.x * 1;
	}
	// if minus......
	if (val.y < 0)
	{
		val.y = val.y * -1;
	}
	// if plus....
	else
	{
		val.y = val.y * 1;
	}
}

void BaseEnemy::ChangeDirection(void)
{
	if (distance.x < 0)
	{
		direction = Direction_Left;
	}
	if(distance.x > 0)
	{
		direction = Direction_Right;
	}
}
