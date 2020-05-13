#include <DxLib.h>

#include "BasePlayer.h"
#include "ImageManager.h"
#include "WeaponInventry.h"

BasePlayer::BasePlayer()
{
	// ｼﾞｬﾝﾌﾟ関係--------------
	jumpForce = 0.0f;
	firstJumpSpeed = -12.0f;
	isJump = false;
	//-------------------------

	// ﾀﾞｯｼｭ関係---------------
	dashTime = DashDefTime;
	isDash = false;
	//-------------------------

	// 重力関係
	gravity = new Gravity();
	// 武器関係----------------
	for (int w = W_Num_1; w < W_Num_Max; w++)
	{
		throwAwayFlag[w] = false;
		inventory[w] = new Inventory((WeaponInventoryNum)w,WEAPON_NONE);
	}
	isHit = false;
	isGet = false;
	registerNum = W_Num_1;
	//-------------------------

	// ｱﾆﾒｰｼｮﾝ関係
	// ｶﾞｰﾄﾞ
	guardTime = 0;
	// 攻撃
	attackCount = 0.0f;
	attackAllowTime = 0;
	levelResetCount = 0;
	oldLevelCount = 0;
	for (int a = ANIM_WAIT; a < ANIM_MAX; a++)
	{
		for (int w = WEAPON_SWORD; w < WEAPON_MAX; w++)
		{
			if (a != ANIM_ATTACK)
			{
				levelCount[a][w] = 0;
			}
			else
			{
				levelCount[a][w] = -1;
			}
		}
	}

	// 消去関係
	deleteFlag = false;
}


BasePlayer::~BasePlayer()
{
}

void BasePlayer::UpDate(const GameController & gameCtl,WeakWeaponList item)
{
	Action(gameCtl,item);
}

bool BasePlayer::AddAnimation(std::string animName, int frame, int interval, bool loop,WEAPON weapon)
{
	animationTable[weapon][animName][Animation_TB_Start] = Animation_TB_Start;
	animationTable[weapon][animName][Animation_TB_Frame] = frame;
	animationTable[weapon][animName][Animation_TB_Interval] = interval;
	animationTable[weapon][animName][Animation_TB_Loop] = loop;

	return true;
}

bool BasePlayer::SetAnimation(std::string animName)
{
	if (BasePlayer::animationName == animName)
	{
		return true;
	}
	if (animationTable[inventory[lpWeaponInventry.GetCurrentWeaponNum()]->GetWeaponType()].find(animName)
		== animationTable[inventory[lpWeaponInventry.GetCurrentWeaponNum()]->GetWeaponType()].end())
	{
		return false;
	}
	BasePlayer::animationName = animName;
	BasePlayer::animationCount = 0;

	return false;
}

void BasePlayer::SetAnimationString(std::string animString, const ANIMATION & anim)
{
	this->animName[anim] = animString;
}

void BasePlayer::Draw(void)
{
	if (FILE_ID(myActionType,
				inventory[lpWeaponInventry.GetCurrentWeaponNum()]->GetWeaponType(),
				levelCount[myActionType][inventory[lpWeaponInventry.GetCurrentWeaponNum()]->GetWeaponType()]).size() == 0)
	{
		return;
	}

	float animationID = 0.0f;
	if (levelCount[myActionType][inventory[lpWeaponInventry.GetCurrentWeaponNum()]->GetWeaponType()]
		!= oldLevelCount)
	{
		animationCount = 0;
	}

	animationCount++;

	if (animationTable[inventory[lpWeaponInventry.GetCurrentWeaponNum()]->GetWeaponType()].find(animationName)
		!= animationTable[inventory[lpWeaponInventry.GetCurrentWeaponNum()]->GetWeaponType()].end())
	{
		/*if (myActionType == ANIM_ATTACK)
		{
			animationID = attackCount;
		}
		else*/
		// ｶﾞｰﾄﾞのｱﾆﾒｰｼｮﾝの際はｱﾆﾒｰｼｮﾝを止める
		//if (myActionType != ANIM_GUARD)
		{
			count = (animationCount
				/ animationTable[inventory[lpWeaponInventry.GetCurrentWeaponNum()]->GetWeaponType()][animationName][Animation_TB_Interval]);

			if (animationTable[inventory[lpWeaponInventry.GetCurrentWeaponNum()]->GetWeaponType()][animationName][Animation_TB_Loop] ||
				count < animationTable[inventory[lpWeaponInventry.GetCurrentWeaponNum()]->GetWeaponType()][animationName][Animation_TB_Frame]
				/ animLevel[myActionType][inventory[lpWeaponInventry.GetCurrentWeaponNum()]->GetWeaponType()])
			{
				// ﾙｰﾌﾟ再生ﾌﾗｸﾞがtrueの場合はそのﾓｰｼｮﾝをﾙｰﾌﾟ再生
				count %= animationTable[inventory[lpWeaponInventry.GetCurrentWeaponNum()]->GetWeaponType()][animationName][Animation_TB_Frame]
					     / animLevel[myActionType][inventory[lpWeaponInventry.GetCurrentWeaponNum()]->GetWeaponType()];
			}
			else
			{
				// ﾙｰﾌﾟ再生ﾌﾗｸﾞがfalseの場合は1ｱﾆﾒｰｼｮﾝが終わり次第待ちﾓｰｼｮﾝにする
				myActionType = ANIM_WAIT;
				count = animationTable[inventory[lpWeaponInventry.GetCurrentWeaponNum()]->GetWeaponType()]
					[animationName][Animation_TB_Frame]
					/ animLevel[myActionType][inventory[lpWeaponInventry.GetCurrentWeaponNum()]->GetWeaponType()] - 1;
			}
			animationID = animationTable[inventory[lpWeaponInventry.GetCurrentWeaponNum()]->GetWeaponType()][animationName][Animation_TB_Start] + count;
		}
	}
	if (animationID < FILE_ID(myActionType,
		inventory[lpWeaponInventry.GetCurrentWeaponNum()]->GetWeaponType(),
		levelCount[myActionType][inventory[lpWeaponInventry.GetCurrentWeaponNum()]->GetWeaponType()]).size())
	{
		switch (direction)
		{
		case Direction_Right:
			DrawRotaGraph(pos.x, pos.y, 1.0f, 0.0f, FILE_ID(myActionType,
				inventory[lpWeaponInventry.GetCurrentWeaponNum()]->GetWeaponType(),
				levelCount[myActionType][inventory[lpWeaponInventry.GetCurrentWeaponNum()]->GetWeaponType()])[animationID], true, true);
			break;
			
		case Direction_Left:
			DrawRotaGraph(pos.x, pos.y, 1.0f, 0.0f, FILE_ID(myActionType,
				inventory[lpWeaponInventry.GetCurrentWeaponNum()]->GetWeaponType(),
				levelCount[myActionType][inventory[lpWeaponInventry.GetCurrentWeaponNum()]->GetWeaponType()])[animationID],
				true, false);
			break;
		default:
			break;
		}
	}

	DrawFormatString(400, 400, 0xffffff, "animID:%f", animationID);
	DrawFormatString(450, 450, 0xffffff, "nowLevel:%d", levelCount[myActionType][inventory[lpWeaponInventry.GetCurrentWeaponNum()]->GetWeaponType()]);
	DrawFormatString(450, 500, 0xffffff, "oldLevel:%d", oldLevelCount);
}
