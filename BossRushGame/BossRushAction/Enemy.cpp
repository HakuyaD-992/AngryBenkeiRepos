#include <DxLib.h>

#include "Enemy.h"
#include "SpriteManager.h"
#include "controlledPlayer.h"


Enemy::Enemy(Vector2 pos, EnemyAnimation anim, ENEMYTYPE type,DIRECTION direction)
{
	this->pos = pos;
	this->myAnimationType = anim;
	this->type = type;
	this->direction = direction;

	AnimationInit(type);

}

Enemy::~Enemy()
{
}

void Enemy::Action(WeakPlayerList playerList)
{
	// calcurate distance between player and enemy
	for (auto player = playerList.lock()->begin(); player != playerList.lock()->end(); player++)
	{
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
		myAnimationType = Eanim_Idle;
	}

	if (IsAttack())
	{
		myAnimationType = Eanim_Attack;
	}

	if (pos.y >= 500)
	{
		pos.y = 500;
		onFloor = true;
	}

	// start animation
	SetAnimation(lpSpriteMng.GetEnemyAnimationString(myAnimationType),type);

}

void Enemy::Draw(void)
{
	BaseEnemy::Draw();
	DrawFormatString(pos.x, pos.y, 0xff0000, "enemy exists");
}

bool Enemy::AnimationInit(ENEMYTYPE eType)
{
	switch (eType)
	{
	case Mandrake:
		AddAnimation("idle", 4, 15, true, eType);
		AddAnimation("run", 6, 15, true, eType);
		AddAnimation("attack", 7, 8, true, eType);
		break;
	case Golem:
		AddAnimation("idle", 4, 15, true, eType);
		AddAnimation("run", 6, 15, true, eType);
		AddAnimation("attack", 18, 8, true, eType);
		break;
	case Werewolf:
		AddAnimation("idle", 4, 15, true, eType);
		AddAnimation("run", 6, 15, true, eType);
		AddAnimation("attack", 7, 8, true, eType);
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
		pos.x += RunSpeed;
		break;
	case Direction_Left:

		myAnimationType = Eanim_Run;
		pos.x -= RunSpeed;
		break;
	case Direction_Max:
		break;
	default:
		break;
	}

}
