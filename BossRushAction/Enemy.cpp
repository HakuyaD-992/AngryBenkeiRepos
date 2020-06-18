#include <DxLib.h>

#include "Enemy.h"
#include "SpriteManager.h"
#include "controlledPlayer.h"
#include "SoundManager.h"
#include "SoundManager.h"
#include "HP.h"
#include "Shot.h"


Enemy::Enemy(Vector2 pos, EnemyAnimation anim, ENEMYTYPE type,DIRECTION direction)
{
	this->pos = pos;
	this->myAnimationType = anim;
	this->type = type;
	this->direction = direction;

	switch (type)
	{
	case BigBoy:
		speed.x = RunSpeed;
		speed.y = RunSpeed;

		maxHP = 51;
		hp = maxHP;
		myFrameRate = 3;
		break;
	case Engineer:
		speed.x = RunSpeed / 2;
		speed.y = RunSpeed / 2;

		maxHP = 130;
		hp = maxHP;
		myFrameRate = 1;
		break;
	case Shieldman:
		speed.x = RunSpeed;
		speed.y = RunSpeed;

		maxHP = 100;
		hp = maxHP;
		myFrameRate = 4;
		break;
	case ETYPE_MAX:
		break;
	default:
		break;
	}

	AnimationInit(type);
	enemySpriteName = lpSpriteMng.GetEnemySpriteName(type);
	SetCollider(lpCollider.GetEnemyColliderData());
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
		playerAnimationType = (*player)->GetMyAnimationType();
		playerRectSize = (*player)->GetColliderRect().size[R_State_Damage][0];
		distance = DistanceCalcurator(playerPos);

		for (auto pShot = (*player)->GetShot()->begin(); pShot != (*player)->GetShot()->end(); pShot++)
		{
			shotDistance = DistanceCalcurator((*pShot)->GetPos());
			if (IsHitObject(shotDistance, (*pShot)->GetSize()))
			{
				(*pShot)->Delete();
				damageFlag = true;
				ChangeVolumeSoundMem(255 * 50 / 100, lpSoundMng.GetSoundID("explosion")[0]);
				PlaySoundMem(lpSoundMng.GetSoundID("explosion")[0], DX_PLAYTYPE_BACK, true);
				break;
			}
		}
		isBehind = (*player)->CheckBehind(pos);
	}



	if (myAnimationType != Eanim_Dead)
	{
		// change direction
		ChangeDirection();

		//if (!isAttackedJump)
		{
			AIAction(distance);
		}
	}

 	rectSize = collider.enemyAnimationRectData[myAnimationType].enemyFrameRectData[animationID].size[R_State_Damage][0];

	if (myAnimationType != Eanim_Dead)
	{
		switch (motionFlag)
		{
		case AI_Run:
			Run();
			break;

		case AI_MoveForward:
			MoveForwardtoPlayer();
			break;
		case AI_GoAround:
			MoveBehindtoPlayer(distance);
			break;
		case AI_Idle:
			break;
		case AI_Attack:
			myAnimationType = Eanim_Attack;
			break;
		case AI_AvoidAttacking:
			//AvoidPlayerAttack();
			break;
		case AI_Max:
			break;
		default:
			break;
		}
	}

	if (myAnimationType == Eanim_Attack)
	{
		HitAttack(playerList);
	}
	if (isHitAttack)
	{
		PlaySoundMem(lpSoundMng.GetEnemySoundID("attack", typeName, type, myAnimationType)[0], DX_PLAYTYPE_BACK, true);
	}

	if (damageFlag)
	{
		switch (type)
		{
		case BigBoy:
			hp -= 10;
			break;
		case Engineer:
			hp -= 5;
			break;
		case Shieldman:
			hp -= 15;
			break;
		case ETYPE_MAX:
			break;
		default:
			break;
		}
		hp--;
		damageFlag = false;
		for (auto player = playerList.lock()->begin(); player != playerList.lock()->end(); player++)
		{
			if (playerAnimationType == ANIMATION::Attack || playerAnimationType == ANIMATION::Attack_Sword)
			{
				if ((*player)->GetAnimationLevelCount((*player)->GetMyAnimationType())
					>= ((*player)->GetAnimationLevelMaxNum((*player)->GetMyAnimationType()) - 1))
				{
					isAttackedJump = true;
				}
			}
		}
	}

	if (knockBackFlag)
	{
		KnockBack(playerList);
	}
	// next task(6/4)
	if (isAttackedJump)
	{
		Jump(playerList);
	}
	else
	{
		attackedForce = AttackedForce_Y;
		attackedJumpSpeed = 0;
		attackedJumpFirstSpeed = AttackedJumpFirstSpeed_Y;
	}
	if (pos.y >= 500)
	{
		pos.y = 500;

		onFloor = true;
		isAttackedJump = false;
	}
	if (hitFlag)
	{
		lpHP.SetEnemyHP(hp, maxHP);
		myAnimationType = Eanim_Hit;
	}

	if (hp <= 0 && myAnimationType != Eanim_Dead)
	{
		hitFlag = false;
		isAttackedJump = true;
		myAnimationType = Eanim_Dead;
	}
	if (myAnimationType == Eanim_Dead)
	{
		if (animationID == 3)
		{
			PlaySoundMem(lpSoundMng.GetEnemySoundID("dead", typeName, type, myAnimationType)[0], DX_PLAYTYPE_BACK, true);
		}
	}
	if (deadFlag)
	{
		explosionFlag = false;
		Delete();
	}

	BoxColliderUpDate();

	// start animation
	SetAnimation(lpSpriteMng.GetEnemyAnimationString(myAnimationType),type);

	myFrame += myFrameRate;
}

void Enemy::Draw(void)
{
	BaseEnemy::Draw();
	DrawFormatString(pos.x, pos.y - 150, 0xffffff, "hp:%d", hp);
	DrawFormatString(400,400,0xff0000, "isJump:%d",isAttackedJump);
	DrawFormatString(100,150, 0xffffff, "jumpForce:%d",attackedForce);
	DrawFormatString(100, 200, 0xffffff, "firstjumpForce:%d", attackedJumpFirstSpeed);

	switch (motionFlag)
	{
	case AI_Run:
		DrawFormatString(600, 30, 0xffffff, "Run");
		break;
	case AI_MoveForward:
		DrawFormatString(600, 30, 0xffffff, "MoveForward");

		break;
	case AI_GoAround:
		DrawFormatString(600, 30, 0xffffff, "GoAround");

		break;
	case AI_Idle:
		DrawFormatString(600, 30, 0xffffff, "Idle");

		break;
	case AI_Attack:
		DrawFormatString(600, 30, 0xffffff, "Attack");

		break;
	case AI_Max:
		break;
	default:
		break;
	}
}

bool Enemy::AnimationInit(ENEMYTYPE eType)
{
	switch (eType)
	{
	case BigBoy:
		AddAnimation("idle", 6, 15, true, eType);
		AddAnimation("walk", 6, 15, true, eType);
		AddAnimation("attack", 10, 8, true, eType);
		AddAnimation("hit", 6, 3, true, eType);
		AddAnimation("dead", 13, 8, true, eType);

		typeName = "BigBoy";
		break;
	case Engineer:
		AddAnimation("idle", 4, 15, true, eType);
		AddAnimation("run", 6, 15, true, eType);
		AddAnimation("attack", 18, 8, true, eType);
		AddAnimation("hit", 3, 7, true, eType);
		AddAnimation("dead", 9, 10, true, eType);
		AddAnimation("avoid", 2, 7, true, eType);

		typeName = "Golem";

		break;
	case Shieldman:
		AddAnimation("idle", 4, 15, true, eType);
		AddAnimation("run", 6, 15, true, eType);
		AddAnimation("attack", 7, 15, true, eType);
		AddAnimation("hit", 3, 7, true, eType);
		AddAnimation("dead", 9, 10, true, eType);
		AddAnimation("avoid", 2, 7, true, eType);

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
		myAnimationType = Eanim_Walk;
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

		myAnimationType = Eanim_Walk;
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

void Enemy::Jump(WeakPlayerList playerList)
{
	for (auto player = playerList.lock()->begin(); player != playerList.lock()->end(); player++)
	{
		if (!(*player)->GetAttackJumpFlag())
		{
			attackedForce = attackedJumpFirstSpeed;
			if (attackedForce <= AttackedJumpFirstSpeed_Y)
			{
				playerDir = (*player)->GetDirection();

			}
			switch (playerDir)
			{
			case Direction_Right:
				pos.x += 14;
				break;
			case Direction_Left:
				pos.x -= 14;
				break;
			default:
				break;
			}
			pos.y += attackedForce;
			attackedJumpFirstSpeed += AttackedForce_Y;
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

void Enemy::AIAction(Vector2 distance)
{
	ClampDistance(distance);
	if (distance.x > 200)
	{
		motionFlag = AI_Run;
	}
	else
	if (isBehind)
	{
		if (myAnimationType != Eanim_Attack && myAnimationType != Eanim_Hit)
		{
			motionFlag = AI_MoveForward;
		}
	} 


	if (!damageFlag)
	{
		//if (!hitFlag)
		{
			if (IsAttack(playerRectSize))
			{
				if (myFrame % 36 == 0)
				{
					motionFlag = AI_AvoidAttacking;
				}
				else
				{
					motionFlag = AI_Attack;
				}
			}
		}
	}
}

void Enemy::MoveForwardtoPlayer(void)
{
	auto angle = atan2(playerPos.y - pos.y, playerPos.x - pos.x);

	pos.x += speed.x * cos(angle);
	pos.y += speed.y * sin(angle);
}

void Enemy::MoveBehindtoPlayer(Vector2 distance)
{
	if (distance.y < 10)
	{
		pos.y -= 1;
		myAnimationType = Eanim_Walk;
	}
	else
	{
		Run();
		switch (direction)
		{
		case Direction_Right:
			if (pos.x > playerPos.x + 60)
			{
				MoveForwardtoPlayer();
			}

			break;
		case Direction_Left:
			if (pos.x < playerPos.x - 60)
			{
				MoveForwardtoPlayer();
			}
			break;
		default:
			break;
		}
	}

}

bool Enemy::Init(void)
{

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
						= Vector2(pos.x + lpCollider.GetEnemyColliderData()[type].enemyAnimationRectData[myAnimationType].enemyFrameRectData[frame].pos[flag][rectNum].x,
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
						= Vector2(pos.x - lpCollider.GetEnemyColliderData()[type].enemyAnimationRectData[myAnimationType].enemyFrameRectData[frame].pos[flag][rectNum].x,
							pos.y + lpCollider.GetEnemyColliderData()[type].enemyAnimationRectData[myAnimationType].enemyFrameRectData[frame].pos[flag][rectNum].y);
				}
			}
		}
		break;
	default:
		break;
	}
}
