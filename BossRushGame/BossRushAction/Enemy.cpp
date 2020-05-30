#include <DxLib.h>

#include "Enemy.h"
#include "SpriteManager.h"
#include "controlledPlayer.h"
#include "SoundManager.h"
#include "SoundManager.h"


Enemy::Enemy(Vector2 pos, EnemyAnimation anim, ENEMYTYPE type,DIRECTION direction)
{
	this->pos = pos;
	this->myAnimationType = anim;
	this->type = type;
	this->direction = direction;

	switch (type)
	{
	case Mandrake:
		speed.x = RunSpeed;
		speed.y = RunSpeed;
		break;
	case Golem:
		speed.x = RunSpeed / 2;
		speed.y = RunSpeed / 2;
		break;
	case Werewolf:
		speed.x = RunSpeed;
		speed.y = RunSpeed;
		break;
	case ETYPE_MAX:
		break;
	default:
		break;
	}

	AnimationInit(type);
	enemySpriteName = lpSpriteMng.GetEnemySpriteName(type);
}

Enemy::~Enemy()
{
}

void Enemy::Action(WeakPlayerList playerList)
{

	oldAnimationType = myAnimationType;
	// calcurate distance between player and enemy
	for (auto player = playerList.lock()->begin(); player != playerList.lock()->end(); player++)
	{
		playerPos = (*player)->GetPos();
		DistanceCalcurator((*player)->GetPos());
	}

	// change direction
	ChangeDirection();

	if (IsFindPlayer())
	{
		// move enemy right or left
		Run();
	}
	else
	{
		if (!damageFlag)
		{
			myAnimationType = Eanim_Idle;
		}
	}

	if (!damageFlag)
	{
		if (IsAttack())
		{
			myAnimationType = Eanim_Attack;
		}
	}

	if (myAnimationType == Eanim_Attack)
	{
		HitAttack(playerList);
	}
	if (isHitAttack)
	{
		PlaySoundMem(lpSoundMng.GetEnemySoundID("attack", typeName, type, myAnimationType)[0],DX_PLAYTYPE_BACK,true);
	}


	if (pos.y >= 500)
	{
		pos.y = 500;
		onFloor = true;
	}

	if (damageFlag)
	{
		hp--;
		damageFlag = false;
		for (auto player = playerList.lock()->begin(); player != playerList.lock()->end(); player++)
		{
			if ((*player)->GetAnimationLevelCount((*player)->GetMyAnimationType())
				>= ((*player)->GetAnimationLevelMaxNum((*player)->GetMyAnimationType()) - 1))
			{
				knockBackFlag = true;
			}
		}
	}

	if (knockBackFlag)
	{
		KnockBack(playerList);
	}

	if (hitFlag)
	{
		myAnimationType = Eanim_Hit;
	}

	BoxColliderUpDate();

	// start animation
	SetAnimation(lpSpriteMng.GetEnemyAnimationString(myAnimationType),type);
}

void Enemy::Draw(void)
{
	BaseEnemy::Draw();
	DrawFormatString(pos.x, pos.y - 150, 0xffffff, "hp:%d", hp);
	DrawFormatString(pos.x, pos.y, 0xff0000, "isHitAttack:%d",isHitAttack);
	DrawFormatString(pos.x, pos.y - 200, 0xffffff, "pos.x:%d,pos.y:%d", pos.x, pos.y);
}

bool Enemy::AnimationInit(ENEMYTYPE eType)
{
	switch (eType)
	{
	case Mandrake:
		AddAnimation("idle", 4, 15, true, eType);
		AddAnimation("run", 6, 15, true, eType);
		AddAnimation("attack", 7, 8, true, eType);
		AddAnimation("hit", 3, 7, true, eType);

		typeName = "Mandrake";
		break;
	case Golem:
		AddAnimation("idle", 4, 15, true, eType);
		AddAnimation("run", 6, 15, true, eType);
		AddAnimation("attack", 18, 8, true, eType);
		AddAnimation("hit", 3, 7, true, eType);

		typeName = "Golem";

		break;
	case Werewolf:
		AddAnimation("idle", 4, 15, true, eType);
		AddAnimation("run", 6, 15, true, eType);
		AddAnimation("attack", 7, 8, true, eType);
		AddAnimation("hit", 3, 7, true, eType);

		typeName = "Werewolf";

		break;
	case ETYPE_MAX:
		break;
	default:
		break;
	}

	return true;
}

void Enemy::Run(void)
{
	switch (direction)
	{
	case Direction_Right:
		myAnimationType = Eanim_Run;
		pos.x += speed.x;
		//if (pos.y > playerPos.y)
		//{
		//	pos.y -= speed.y;
		//}
		//else
		//{
		//	pos.y += speed.y;
		//}

		break;
	case Direction_Left:

		myAnimationType = Eanim_Run;
		pos.x -= speed.x;
		//if (pos.y > playerPos.y)
		//{
		//	pos.y -= speed.y;
		//}
		//else
		//{
		//	pos.y += speed.y;
		//}
		break;
	case Direction_Max:
		break;
	default:
		break;
	}

}

void Enemy::KnockBack(WeakPlayerList playerList)
{
	for (auto player = playerList.lock()->begin(); player != playerList.lock()->end(); player++)
	{
		if (kbSpeed <= 0.0f)
		{
			playerDir = (*player)->GetDirection();
		}
		kbAccel += E_KnockBackAccelSP;
		kbFirstSpeed -= kbAccel;
		kbSpeed = kbFirstSpeed;
		if (kbSpeed <= 0)
		{
			kbSpeed = 0;
			kbFirstSpeed = E_KnockBackFirstSP;
			kbAccel = 0;
			knockBackFlag = false;
		}

		switch (playerDir)
		{
		case Direction_Right:
			pos.x += kbSpeed;
			break;
		case Direction_Left:
			pos.x -= kbSpeed;
			break;
		default:
			break;
		}
	}
}

void Enemy::HitAttack(WeakPlayerList playerList)
{
	for (auto player = playerList.lock()->begin(); player != playerList.lock()->end(); player++)
	{
		if (!(*player)->GetKnockbackFlag())
		{
			if ((*player)->IsHitEnemyAttack(collider.enemyAnimationRectData[myAnimationType].enemyFrameRectData[animationID]))
			{
				isHitAttack = true;
				break;
			}
			else
			{
				isHitAttack = false;
			}
		}
		else
		{
			isHitAttack = false;
		}
	}
}

//void Enemy::GoAroundBackofPlayer(void)
//{
//	switch (direction)
//	{
//	case Direction_Right:
//		if (pos.x < playerPos.x - 75)
//		{
//			pos.x += speed.x * 2;
//		}
//		else
//		{
//			moveY = true;
//		}
//
//		break;
//	case Direction_Left:
//		if (pos.x > playerPos.x + 75)
//		{
//			pos.x -= speed.x * 2;
//		}
//		else
//		{
//			moveY = true;
//		}
//		break;
//	default:
//		break;
//	}
//
//	if (moveY)
//	{
//		if (pos.y < playerPos.y)
//		{
//			pos.x -= speed.x;
//			pos.y += speed.y;
//			if (pos.y >= playerPos.y)
//			{
//				moveY = false;
//			}
//		}
//		else
//		{
//			pos.x += speed.x;
//			pos.y -= speed.y;
//			if (pos.y <= playerPos.y)
//			{
//				moveY = false;
//			}
//		}
//	}
//}

bool Enemy::Init(void)
{
	canGoaround = false;
	moveY = false;
	return true;
}

void Enemy::BoxColliderUpDate(void)
{
	switch (direction)
	{
	case Direction_Right:
		for (int flag = R_State_Damage; flag < R_State_Max; flag++)
		{
			for (int frame = 0;
				frame < collider.enemyAnimationRectData[myAnimationType].enemyFrameRectData.size();
				frame++)
			{
				for (int rectNum = 0;
					rectNum < collider.enemyAnimationRectData[myAnimationType].enemyFrameRectData[frame].rectNum[flag];
					rectNum++)
				{
					collider.enemyAnimationRectData[myAnimationType].enemyFrameRectData[frame].pos[flag][rectNum]
						= Vector2(pos.x - lpCollider.GetEnemyColliderData()[type].enemyAnimationRectData[myAnimationType].enemyFrameRectData[frame].pos[flag][rectNum].x,
							pos.y + lpCollider.GetEnemyColliderData()[type].enemyAnimationRectData[myAnimationType].enemyFrameRectData[frame].pos[flag][rectNum].y);
				}
			}
		}
		break;
	case Direction_Left:
		for (int flag = R_State_Damage; flag < R_State_Max; flag++)
		{
			for (int frame = 0;
				frame < collider.enemyAnimationRectData[myAnimationType].enemyFrameRectData.size();
				frame++)
			{
				for (int rectNum = 0;
					rectNum < collider.enemyAnimationRectData[myAnimationType].enemyFrameRectData[frame].rectNum[flag];
					rectNum++)
				{
					collider.enemyAnimationRectData[myAnimationType].enemyFrameRectData[frame].pos[flag][rectNum]
						= Vector2(pos.x + lpCollider.GetEnemyColliderData()[type].enemyAnimationRectData[myAnimationType].enemyFrameRectData[frame].pos[flag][rectNum].x,
							pos.y + lpCollider.GetEnemyColliderData()[type].enemyAnimationRectData[myAnimationType].enemyFrameRectData[frame].pos[flag][rectNum].y);
				}
			}
		}
		break;
	default:
		break;
	}
}
