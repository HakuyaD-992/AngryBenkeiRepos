#include <DxLib.h>

#include "SpriteManager.h"
#include "controlledPlayer.h"
#include "GameController.h"
#include "Collider.h"
#include "SoundManager.h"
#include "HP.h"
#include "Shot.h"


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

	animInitFlag = false;
	// update hp
	lpHP.UpdatePlayerHP(hp,MAXHP);

	oldAnimationType = myAnimationType;

	DeleteShot();
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
	}

	if (pos.y >= 500)
	{
		pos.y = 500;
		onFloor = true;
	}
	else
	{
		onFloor = false;
	}
	// player stand on floor
	if (onFloor)
	{
		if (!attackFlag)
		{
			myAnimationType = Idle;
		}
		startingJumpForce = -10.0f;
		jumpForce = { 0,0 };
		isJump = false;
	}


	if (!attackFlag && !hitFlag)
	{
		// move left
		if (inputNow[1])
		{
			animInitFlag = true;
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
			animInitFlag = true;

			pos.x += 3;
			direction = Direction_Right;
			if (!isJump)
			{
				myAnimationType = Run;
			}
			damageCount = 0;
		}

		if (inputNow[3])
		{
			animInitFlag = true;

			pos.y -= 1;
			if (!isJump)
			{
				myAnimationType = Run;
			}
			damageCount = 0;
		}
		if (inputNow[0])
		{
			animInitFlag = true;

			pos.y += 1;
			if (!isJump)
			{
				myAnimationType = Run;
			}
			damageCount = 0;
		}
	}

	if (hp <= 0)
	{
		Delete();
		
		for (auto enemy = enemyList.lock()->begin(); enemy != enemyList.lock()->end(); enemy++)
		{
			(*enemy)->Delete();
		}
	}


	if (knockbackFlag)
	{
		myAnimationType = ANIMATION::KnockDown;
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

	for (auto shot = shotList->begin(); shot != shotList->end(); shot++)
	{
		(*shot)->Action();
	}

	if (myAnimationType != oldAnimationType)
	{
		animationID = 0;
	}

	if (myAnimationType == ANIMATION::Attack ||
		myAnimationType == ANIMATION::Attack_Sword ||
		myAnimationType == ANIMATION::Attack_Jump_Sword)
	{
		attackMotionFlag = true;
	}
	else
	{
		attackMotionFlag = false;
	}

	// update box collider position
	BoxColliderUpDate();

	if (attackFlag)
	{
		HitAttack(enemyList);
	}
	// add shot interval per flame
	shotIntervalCount++;
	// animation
	SetAnimation(lpSpriteMng.GetPlayerAnimationString(myAnimationType));
}

void controlledPlayer::Draw(void)
{
	BasePlayer::Draw();

	for (auto shot = shotList->begin(); shot != shotList->end(); shot++)
	{
		(*shot)->Draw();
	}


	DrawFormatString(0, 0, 0xffffff, "player existing");

	DrawFormatString(100, 100, 0xffffff, "pos.x:%dpos.y:%d", pos.x, pos.y);

	DrawFormatString(pos.x, pos.y - 300, 0xffffff, "knockback:%d", knockbackFlag);
	DrawFormatString(pos.x, pos.y - 350, 0xffffff, "nowanimation:%d", myAnimationType);


	DrawFormatString(pos.x, pos.y - 200, 0xffffff, "gauge:%d", gaugeCount);
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
	shotCount = 0;
	shotDir = direction;
	if (!shotList)
	{
		shotList = make_shared<SharedShotList>();
	}
}


void controlledPlayer::AnimationInit(void)
{
	AddAnimation("idle", 5, 15, true);
	AddAnimation("jump", 4, 20, true);
	AddAnimation("run", 6, 15, true);
	AddAnimation("attack", 17, 7, true);
	AddAnimation("hit", 3, 10, true);
	AddAnimation("attack_sword", 18, 6, true);
	AddAnimation("knockdown", 6, 10, true);
	AddAnimation("summersault", 3, 10, true);
}

void controlledPlayer::Jump(void)
{
	jumpForce.y = startingJumpForce;
	pos.y += jumpForce.y;
	// ¼Þ¬ÝÌß‚Ì—Í‚ª‰‚ßÏ²Å½‚È‚Ì‚ÅA¼Þ¬ÝÌß‚Ì—Í‚Éd—Í•ªÌß×½‚µ‚Ä‚â‚é‚±‚Æ‚Å‚¾‚ñ‚¾‚ñd—Í‚ª‚©‚©‚Á‚½‚æ‚¤‚É‚È‚é
	startingJumpForce += GRAVITY;
	if (startingJumpForce >= 0)
	{
		myAnimationType = SummerSault;
	}
}

void controlledPlayer::Attack(const GameController& gameCtl,WeakEnemyList enemyList)
{
	auto now = gameCtl.GetPadInfo().padInputNow;
	auto old = gameCtl.GetPadInfo().padInputOld;

	for (auto enemy = enemyList.lock()->begin(); enemy != enemyList.lock()->end(); enemy++)
	{
		DistanceCalcurator((*enemy)->GetPos());
		if (distance >= farestEnemyPos)
		{
			(*enemy)->GetIsFarest() = true;
		}
		if (!(*enemy)->GetHitFlag())
		{
			canAttack = true;
		}
		else
		{
			canAttack = false;
		}
	}

	ChangeVolumeSoundMem(255 * 50 / 100,lpSoundMng.GetPlayerSoundEffectID("attack", animLevelCount[myAnimationType])[0]);


	//if (canAttack)
	{
		if (!attackFlag)
		{
			if (cannextAttackFlag)
			{
				if (!nextAttackFlag[0] || !nextAttackFlag[1])
				{
					if (now[6] && !old[6])
					{
						nextAttackFlag[0] = true;
					}
					if (now[7] && !old[7])
					{
						nextAttackFlag[1] = true;
					}
				}
			}
			else
			{
				if (now[6] && !old[6])
				{
					myAnimationType = ANIMATION::Attack;

					PlaySoundMem(lpSoundMng.GetPlayerSoundEffectID("swing", animLevelCount[myAnimationType])[0], DX_PLAYTYPE_BACK, true);

					PlaySoundMem(lpSoundMng.GetPlayerSoundEffectID("attack", animLevelCount[myAnimationType])[0], DX_PLAYTYPE_BACK, true);

					attackFlag = true;
					animationID = 0;
				}
				if (now[7] && !old[7])
				{
					myAnimationType = ANIMATION::Attack_Sword;

					PlaySoundMem(lpSoundMng.GetPlayerSoundEffectID("swing", animLevelCount[myAnimationType])[0], DX_PLAYTYPE_BACK, true);

					PlaySoundMem(lpSoundMng.GetPlayerSoundEffectID("attack", Level_5)[0], DX_PLAYTYPE_BACK, true);

					attackFlag = true;
					animationID = 0;
				}
			} 

		}
		if (nextAttackFlag)
		{
			if (now[6] && !old[6])
			{
				myAnimationType = ANIMATION::Attack;

				PlaySoundMem(lpSoundMng.GetPlayerSoundEffectID("swing", animLevelCount[myAnimationType])[0], DX_PLAYTYPE_BACK, true);
				PlaySoundMem(lpSoundMng.GetPlayerSoundEffectID("attack", animLevelCount[myAnimationType])[0], DX_PLAYTYPE_BACK, true);

				attackFlag = true;
				animationID = 0;
			}
		}
		if (shotCount >= 4 || gaugeCount < 5)
		{
			shotFlag = false;
			shotIntervalCount = 0;
			shotCount = 0;
		}
	}

	if (isHitAttack)
	{
		ChangeVolumeSoundMem(255 * 55 / 100, lpSoundMng.GetPlayerSoundID(animString[myAnimationType], myAnimationType, animLevelCount[myAnimationType])[0]);

		PlaySoundMem(lpSoundMng.GetPlayerSoundID(animString[myAnimationType], myAnimationType, animLevelCount[myAnimationType])[0], DX_PLAYTYPE_BACK, true);
	}
}

void controlledPlayer::HitAttack(WeakEnemyList enemyList)
{
	for (auto enemy = enemyList.lock()->begin(); enemy != enemyList.lock()->end(); enemy++)
	{
		if ((*enemy)->GetmyAnimationType() != Eanim_Dead)
		{
			if ((*enemy)->IsHitPlayerAttack(collider[myAnimationType].playerAnimLevelData[animLevelCount[myAnimationType]].playerRectData[animationID]))
			{
				gaugeCount += 3;

				isHitAttack = true;
				isHitEnemyType = (*enemy)->GetType();
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

	// if enemy dead all, isHitAttack = false
	if (enemyList.lock()->size() <= 0)
	{
		isHitAttack = false;
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

void controlledPlayer::DeleteShot(void)
{
	SharedShotList deleteShotList(shotList->size());
	(*shotList).remove_if([](SharedShotPtr& obj) {return (obj->GetDeleteflag()); });
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
