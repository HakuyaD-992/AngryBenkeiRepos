#include <DxLib.h>

#include "SpriteManager.h"
#include "controlledPlayer.h"
#include "GameController.h"


controlledPlayer::controlledPlayer(Vector2 pos, ANIMATION anim,DIRECTION direction)
{
	this->pos = pos;
	this->myAnimationType = anim;
	this->direction = direction;

	AnimationInit();
}

controlledPlayer::~controlledPlayer()
{
}

void controlledPlayer::Action(const GameController & gameCtl)
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


	if (!attackFlag)
	{
		// move left
		if (inputNow[1])
		{
			pos.x -= 5;
			direction = Direction_Left;
			if (!isJump)
			{
				myAnimationType = Run;
			}
		}
		// move right
		if (inputNow[2])
		{
			pos.x += 5;
			direction = Direction_Right;
			if (!isJump)
			{
				myAnimationType = Run;
			}
		}
	}

	Attack(gameCtl);

	// animation
	SetAnimation(lpSpriteMng.GetPlayerAnimationString(myAnimationType));
}

void controlledPlayer::Draw(void)
{
	BasePlayer::Draw();
	DrawFormatString(0, 0, 0xffffff, "player existing");

	DrawFormatString(100, 100, 0xffffff, "pos.x:%dpos.y:%d", pos.x, pos.y);

	DrawFormatString(pos.x, pos.y - 300, 0xffffff, "oldAnimation:%d", oldAnimationType);
	DrawFormatString(pos.x, pos.y - 350, 0xffffff, "nowanimation:%d", myAnimationType);


	DrawFormatString(pos.x, pos.y - 200, 0xffffff, "oldLevel:%d", oldLevel);
	DrawFormatString(pos.x, pos.y - 250, 0xffffff, "animationLevel:%d", animLevel[myAnimationType]);
	DrawFormatString(pos.x, pos.y -380, 0xffffff, "nouPush:%d", notPushCount);
}

void controlledPlayer::AnimationInit(void)
{
	AddAnimation("idle", 5, 15, true);
	AddAnimation("jump", 4, 15, false);
	AddAnimation("fall", 2, 15, false);
	AddAnimation("run", 6, 15, true);
	AddAnimation("summersault", 3, 10, true);

	AddAnimation("attack_sword", 17, 5, false);
	AddAnimation("kick", 8, 5, false);
	AddAnimation("punch", 13, 5, false);
}

void controlledPlayer::Jump(void)
{
	//actionFlag = true;
	jumpForce.y = startingJumpForce;
	pos.y += jumpForce.y;
	// ¼Þ¬ÝÌß‚Ì—Í‚ª‰‚ßÏ²Å½‚È‚Ì‚ÅA¼Þ¬ÝÌß‚Ì—Í‚Éd—Í•ªÌß×½‚µ‚Ä‚â‚é‚±‚Æ‚Å‚¾‚ñ‚¾‚ñd—Í‚ª‚©‚©‚Á‚½‚æ‚¤‚É‚È‚é
	startingJumpForce += GRAVITY;

}

void controlledPlayer::Attack(const GameController& gameCtl)
{
	auto now = gameCtl.GetPadInfo().padInputNow;
	auto old = gameCtl.GetPadInfo().padInputOld;

	if (!attackFlag)
	{
		if (now[4] && !old[4])
		{
			myAnimationType = Attack_Sword;
			attackFlag = true;
			animLevelCount[myAnimationType] = (AnimationLevel)(animLevelCount[myAnimationType] + 1);
		}
		if (now[7] && !old[7])
		{
			myAnimationType = Kick;
			attackFlag = true;
			animLevelCount[myAnimationType] = (AnimationLevel)(animLevelCount[myAnimationType] + 1);
		}
		if (now[6] && !old[6])
		{
			myAnimationType = Punch;
			attackFlag = true;
			animLevelCount[myAnimationType] = (AnimationLevel)(animLevelCount[myAnimationType] + 1);
		}
	}
	if (animLevelCount[myAnimationType] >= animLevel[myAnimationType])
	{
		animLevelCount[myAnimationType] = (AnimationLevel)(Level_None - 1);
		notPushCount = 0;
		myAnimationType = Idle;
		attackFlag = false;
	}
}
