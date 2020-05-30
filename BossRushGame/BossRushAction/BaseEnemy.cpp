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
	damageFlag = false;
	hitFlag = false;
	isHitAttack = false;

	intoSightRangeFlag = false;
	sightRange = SightRange;
	hp = MAXHP;

	knockBackFlag = false;
	kbFirstSpeed = E_KnockBackFirstSP;
	kbAccel = 0;
	kbSpeed = 0;
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
	if (enemySpriteName[myAnimationType].size() - 1 == 0)
	{
		return;
	}

	animationID = 0;
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

		if (count >= enemySpriteName[myAnimationType].size() - 1)
		{
			hitFlag = false;
		}

		if (myAnimationType != oldAnimationType)
		{
			count = 0;
		}

		animationID = animationTable[type][animationName][Animation_TB_Start] + count;
	}
	if (animationID < enemySpriteName[myAnimationType].size())
	{
		switch (direction)
		{
		case Direction_Right:
			DrawRotaGraph(pos.x, pos.y, 1.0f, 0.0f,
				lpSpriteMng.GetEnemyID(enemySpriteName, myAnimationType,type)[animationID],
				true, true);
			break;

		case Direction_Left:
			DrawRotaGraph(pos.x, pos.y, 1.0f, 0.0f,
				lpSpriteMng.GetEnemyID(enemySpriteName, myAnimationType,type)[animationID],
				true, false);
			break;
		default:
			break;
		}
		DrawBoxCollider();
	}

	
	DrawFormatString(pos.x, pos.y - 100, 0xffffff, "myAnimationType:%d", myAnimationType);
	DrawFormatString(pos.x, pos.y - 50, 0xffffff, "animationID:%d",animationID);

}

void BaseEnemy::DrawBoxCollider(void)
{
	auto tmpColliderBox = collider.enemyAnimationRectData[myAnimationType].enemyFrameRectData[animationID];

	for (int flag = R_State_Damage; flag < R_State_Max; flag++)
	{
		for (int colliderNum = 0; colliderNum < tmpColliderBox.rectNum[flag]; colliderNum++)
		{
			auto colliderPos = tmpColliderBox.pos[flag][colliderNum];
			auto colliderSize = tmpColliderBox.size[flag][colliderNum];

			if (flag == R_State_Attack)
			{
				boxColliderColor = 0xff0000;
			}
			else
			{
				boxColliderColor = 0x0000ff;
			}
			DrawBox(colliderPos.x - (colliderSize.x / 2),
				colliderPos.y - (colliderSize.y / 2),
				colliderPos.x + (colliderSize.x / 2),
				colliderPos.y + (colliderSize.y / 2),
				boxColliderColor, false);
		}
	}
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

void BaseEnemy::SetCollider(const EnemyRectData & enemyCollider)
{
	this->collider = enemyCollider[type];
}

bool BaseEnemy::Init(const EnemyAnimSprite& enemySpriteName)
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
		if (distance.x >= collider.enemyAnimationRectData[myAnimationType].enemyFrameRectData[animationID].size[R_State_Damage][0].x &&
			distance.y >= collider.enemyAnimationRectData[myAnimationType].enemyFrameRectData[animationID].size[R_State_Damage][0].y)
		{
			intoSightRangeFlag = false;
		}
		else
		{
			intoSightRangeFlag = true;
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

bool BaseEnemy::IsHitPlayerAttack(const ActionRect & playerRect)
{
	
	if (!hitFlag)
	{
		Vector2 e_distance;
		auto attackRect = playerRect;
		auto damageRect = collider.enemyAnimationRectData[myAnimationType].enemyFrameRectData[animationID];
		for (int atcRNum = 0; atcRNum < attackRect.rectNum[R_State_Attack]; atcRNum++)
		{
			for (int damRNum = 0; damRNum < damageRect.rectNum[R_State_Damage]; damRNum++)
			{
				e_distance = attackRect.pos[R_State_Attack][atcRNum] - damageRect.pos[R_State_Damage][damRNum];
				ClampDistance(e_distance);

				if (e_distance.x <= ((attackRect.size[R_State_Attack][atcRNum].x / 2)
					+ (damageRect.size[R_State_Damage][damRNum].x / 2))
					&& e_distance.y <= ((attackRect.size[R_State_Attack][atcRNum].y / 2)
						+ (damageRect.size[R_State_Damage][damRNum].y / 2)))
				{
					hitFlag = true;
					damageFlag = true;
					return damageFlag;
				}
				else
				{
					hitFlag = false;
					damageFlag = false;
				}
			}
		}
	}
	return damageFlag;
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
