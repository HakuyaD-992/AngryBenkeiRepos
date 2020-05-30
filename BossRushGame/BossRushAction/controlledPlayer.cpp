#include <DxLib.h>

#include "SpriteManager.h"
#include "controlledPlayer.h"
#include "GameController.h"
#include "Collider.h"
#include "SoundManager.h"


controlledPlayer::controlledPlayer(Vector2 pos, ANIMATION anim,DIRECTION direction)
{
	this->pos = pos;
	this->myAnimationType = anim;
	this->direction = direction;

	AnimationInit();
	Init();
}

controlledPlayer::~controlledPlayer()
{
}

void controlledPlayer::Action(const GameController & gameCtl, WeakEnemyList enemyList)
{
	auto inputNow = gameCtl.GetPadInfo().padInputNow;
	auto inputOld = gameCtl.GetPadInfo().padInputOld;

	oldAnimationType = myAnimationType;
	// jump
	if (!attackFlag)
	{
		if (inputNow[5] && !inputOld[5])
		{
			isJump = true;
			onFloor = false;
		}
		if (isJump)
		{
			myAnimationType = ANIMATION::Jump;
			Jump();
	
		}
		// jump -> fall
		if (startingJumpForce >= 0)
		{
			myAnimationType = SummerSault;

		}
	}
	// player stand on floor
	if (onFloor)
	{
		if (myAnimationType != Punch && myAnimationType != Attack_Sword && myAnimationType != Kick)
		{
			myAnimationType = Idle;

		}
		startingJumpForce = -10.0f;
		jumpForce = { 0,0 };
		isJump = false;
	}
	if (pos.y >= 500)
	{
		pos.y = 500;
		onFloor = true;
	}

	if (!attackFlag && !hitFlag)
	{
		// move left
		if (inputNow[1])
		{
			pos.x -= 3;
			direction = Direction_Left;
			if (!isJump)
			{
				myAnimationType = Run;
			}
			damageCount = 0;
		}
		// move right
		if (inputNow[2])
		{
			pos.x += 3;
			direction = Direction_Right;
			if (!isJump)
			{
				myAnimationType = Run;
			}
			damageCount = 0;

		}

	}

	if (knockbackFlag)
	{
		myAnimationType = ANIMATION::KnockBack;
	}
	if (damageFlag)
	{
		hp--;
		damageCount++;
		if (damageCount >= 3)
		{
			knockbackFlag = true;
			damageCount = 0;
		}
		damageFlag = false;
	}

	if (hitFlag && !knockbackFlag)
	{
		myAnimationType = Hit;
	}

	if (!damageFlag && !knockbackFlag && !hitFlag)
	{
		// attack
		Attack(gameCtl, enemyList);
	}

	if (myAnimationType != oldAnimationType)
	{
		animationID = 0;
	}

	// update box collider position
	BoxColliderUpDate();

	// animation
	SetAnimation(lpSpriteMng.GetPlayerAnimationString(myAnimationType));
}

void controlledPlayer::Draw(void)
{
	BasePlayer::Draw();
	DrawFormatString(0, 0, 0xffffff, "player existing");

	DrawFormatString(100, 100, 0xffffff, "pos.x:%dpos.y:%d", pos.x, pos.y);

	DrawFormatString(pos.x, pos.y - 300, 0xffffff, "knockback:%d", knockbackFlag);
	DrawFormatString(pos.x, pos.y - 350, 0xffffff, "nowanimation:%d", myAnimationType);


	DrawFormatString(pos.x, pos.y - 200, 0xffffff, "oldLevel:%d", oldLevel);
	DrawFormatString(pos.x, pos.y - 250, 0xffffff, "animationLevel:%d", animLevel[myAnimationType]);
	DrawFormatString(pos.x, pos.y -380, 0xffffff, "hp:%d", hp);

	//for (int f = R_State_Damage; f < R_State_Max; f++)
	{
		for (int rectNum = 0; rectNum < collider[myAnimationType].playerAnimLevelData[animLevelCount[myAnimationType]].playerRectData[animationID].rectNum[R_State_Attack];
			rectNum++)
		{
			auto colPos = collider[myAnimationType].playerAnimLevelData[animLevelCount[myAnimationType]].playerRectData[animationID].pos;
			DrawFormatString(280, 20 + (rectNum * 50), 0xffffff, "rectPos.x:%d,rectPos.y:%d", colPos[R_State_Attack][rectNum].x, colPos[R_State_Attack][rectNum].y);
		}
	}
}

void controlledPlayer::Init(void)
{
	canAttack = false;
}


void controlledPlayer::AnimationInit(void)
{
	AddAnimation("idle", 5, 15, true);
	AddAnimation("jump", 4, 15, false);
	AddAnimation("fall", 2, 15, false);
	AddAnimation("run", 6, 15, true);
	AddAnimation("summersault", 3, 10, true);

	AddAnimation("attack_sword", 10, 3, false);
	AddAnimation("kick", 8, 5, false);
	AddAnimation("punch", 13, 5, false);
	AddAnimation("walk", 6, 10, true);
	AddAnimation("hit", 3, 5, true);
	AddAnimation("knockback", 6, 10, true);
}

void controlledPlayer::Jump(void)
{
	//actionFlag = true;
	jumpForce.y = startingJumpForce;
	pos.y += jumpForce.y;
	// ¼Þ¬ÝÌß‚Ì—Í‚ª‰‚ßÏ²Å½‚È‚Ì‚ÅA¼Þ¬ÝÌß‚Ì—Í‚Éd—Í•ªÌß×½‚µ‚Ä‚â‚é‚±‚Æ‚Å‚¾‚ñ‚¾‚ñd—Í‚ª‚©‚©‚Á‚½‚æ‚¤‚É‚È‚é
	startingJumpForce += GRAVITY;

}

void controlledPlayer::Attack(const GameController& gameCtl,WeakEnemyList enemyList)
{
	auto now = gameCtl.GetPadInfo().padInputNow;
	auto old = gameCtl.GetPadInfo().padInputOld;

	for (auto enemy = enemyList.lock()->begin(); enemy != enemyList.lock()->end(); enemy++)
	{
		if (!(*enemy)->GetHitFlag())
		{
			canAttack = true;
		}
		else
		{
			canAttack = false;
		}
	}

	if (canAttack)
	{
		if (!attackFlag)
		{
			if (now[4] && !old[4])
			{
				animationID = 0;
				myAnimationType = Attack_Sword;
				attackFlag = true;
			}
			if (now[7] && !old[7])
			{

				animationID = 0;
				myAnimationType = Kick;
				attackFlag = true;
			}

			if (now[6] && !old[6])
			{

				animationID = 0;
				myAnimationType = Punch;
				attackFlag = true;
			}
		}
	}
	if (attackFlag)
	{
		HitAttack(enemyList);
	}

	if (isHitAttack)
	{
		PlaySoundMem(lpSoundMng.GetPlayerSoundID(animString[myAnimationType], myAnimationType, animLevelCount[myAnimationType])[0], DX_PLAYTYPE_BACK, true);
		//isHitAttack = false;
	}
}

void controlledPlayer::HitAttack(WeakEnemyList enemyList)
{
	for (auto enemy = enemyList.lock()->begin(); enemy != enemyList.lock()->end(); enemy++)
	{
		if ((*enemy)->IsHitPlayerAttack(collider[myAnimationType].playerAnimLevelData[animLevelCount[myAnimationType]].playerRectData[animationID]))
		{
			isHitAttack = true;
			break;
		}
		else
		{
			isHitAttack = false;
		}
	}
}

void controlledPlayer::KnockBack(WeakEnemyList enemyList)
{
	for (auto enemy = enemyList.lock()->begin(); enemy != enemyList.lock()->end(); enemy++)
	{
		if ((*enemy)->GetHitAttack())
		{
			if (kbAccel <= 0.0f)
			{
				enemyDir = (*enemy)->GetDirection();
			}
			kbAccel += P_KnockBackAccelSP;
			kbFirstSpeed += kbAccel;
			kbSpeed = kbFirstSpeed;
			if (onFloor)
			{
				kbSpeed = 0;
				kbFirstSpeed = P_KnockBackFirstSP;
				kbAccel = 0;
				//knockbackFlag = false;
			}
			switch (enemyDir)
			{
			case Direction_Right:
				pos.x += 3;
				break;
			case Direction_Left:
				pos.x -= 3;
				break;
			default:
				break;
			}
			pos.y -= kbSpeed;
		}
	}
}

void controlledPlayer::BoxColliderUpDate(void)
{
	switch (direction)
	{
	case Direction_Right:
		for (int flag = R_State_Damage; flag < R_State_Max; flag++)
		{
			for (int frame = 0; frame < collider[myAnimationType].playerAnimLevelData[animLevelCount[myAnimationType]].playerRectData.size();
				frame++)
			{
				for (int rectNum = 0;
					rectNum < collider[myAnimationType].playerAnimLevelData[animLevelCount[myAnimationType]].playerRectData[frame].rectNum[flag];
					rectNum++)
				{
					collider[myAnimationType].playerAnimLevelData[animLevelCount[myAnimationType]].playerRectData[frame].pos[flag][rectNum]
						= Vector2(pos.x + lpCollider.GetPlayerColliderData()[myAnimationType].playerAnimLevelData[animLevelCount[myAnimationType]].playerRectData[frame].pos[flag][rectNum].x,
							pos.y + lpCollider.GetPlayerColliderData()[myAnimationType].playerAnimLevelData[animLevelCount[myAnimationType]].playerRectData[frame].pos[flag][rectNum].y);
				}
			}
		}
		break;
	case Direction_Left:
		for (int flag = R_State_Damage; flag < R_State_Max; flag++)
		{
			for (int frame = 0; frame < collider[myAnimationType].playerAnimLevelData[animLevelCount[myAnimationType]].playerRectData.size();
				frame++)
			{
				for (int rectNum = 0;
					rectNum < collider[myAnimationType].playerAnimLevelData[animLevelCount[myAnimationType]].playerRectData[frame].rectNum[flag];
					rectNum++)
				{
					collider[myAnimationType].playerAnimLevelData[animLevelCount[myAnimationType]].playerRectData[frame].pos[flag][rectNum]
						= Vector2(pos.x - lpCollider.GetPlayerColliderData()[myAnimationType].playerAnimLevelData[animLevelCount[myAnimationType]].playerRectData[frame].pos[flag][rectNum].x,
							pos.y + lpCollider.GetPlayerColliderData()[myAnimationType].playerAnimLevelData[animLevelCount[myAnimationType]].playerRectData[frame].pos[flag][rectNum].y);
				}
			}
		}
		break;
	default:
		break;
	}
	
}
