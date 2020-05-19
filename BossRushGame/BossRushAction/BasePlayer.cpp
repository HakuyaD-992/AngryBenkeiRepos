#include <DxLib.h>

#include "BasePlayer.h"
#include "SpriteManager.h"


BasePlayer::BasePlayer()
{
	// initialize animation level count
	animLevelCount = {
		Level_None,
		(AnimationLevel)(Level_None - 1),
		(AnimationLevel)(Level_None - 1),
		Level_None,
		(AnimationLevel)(Level_None - 1),
		Level_None,
		Level_None,
		Level_None,
		Level_None,
		Level_None,
	};
	//instance gravity
	gravity = new Gravity();

	onFloor = false;

	isJump = false;
	startingJumpForce = -10.0f;
	jumpForce = { 0,0 };

	attackFlag = false;
	notPushCount = 0;
}


BasePlayer::~BasePlayer()
{
}

void BasePlayer::UpDate(const GameController & gameCtl)
{
	if (!isJump && !onFloor)
	{
		gravity->PutGravityOnActor(pos);
	}
	Action(gameCtl);
}

bool BasePlayer::Init(PlayerSprite playerSpriteName, std::array<AnimationLevel, Animation_Max> animLevel)
{
	playerSpriteFileName = playerSpriteName;
	this->animLevel = animLevel;
	return true;
}

void BasePlayer::Draw(void)
{
	if (playerSpriteFileName[myAnimationType][animLevelCount[myAnimationType]].size() - 1 == 0)
	{
		return;
	}

	float animationID = 0.0f;

	if (animationTable.find(animationName) != animationTable.end())
	{
		{
			if (myAnimationType != Attack_Sword && myAnimationType != Punch && myAnimationType != Kick)
			{
				animationCount++;

				count = (animationCount / animationTable[animationName][Animation_TB_Interval]);

				if (animationTable[animationName][Animation_TB_Loop] ||
					count < animationTable[animationName][Animation_TB_Frame]
					/ playerSpriteFileName[myAnimationType][animLevelCount[myAnimationType]].size())
				{
					// Ù°ÌßÄ¶Ì×¸Þ‚ªtrue‚Ìê‡‚Í‚»‚ÌÓ°¼®Ý‚ðÙ°ÌßÄ¶
					count %= playerSpriteFileName[myAnimationType][animLevelCount[myAnimationType]].size();
				}
				else
				{
					// Ù°ÌßÄ¶Ì×¸Þ‚ªfalse‚Ìê‡‚Í1±ÆÒ°¼®Ý‚ªI‚í‚èŽŸ‘æ‘Ò‚¿Ó°¼®Ý‚É‚·‚é
					//myActionType = ANIM_WAIT;
					count = animationTable[animationName][Animation_TB_Frame]
						/ (playerSpriteFileName[myAnimationType][animLevelCount[myAnimationType]].size());
				}
			}
			else
			{
				if (attackFlag)
				{
					animationCount++;
					count = (animationCount / animationTable[animationName][Animation_TB_Interval]);
				}

				if (count > playerSpriteFileName[myAnimationType][animLevelCount[myAnimationType]].size() - 1)
				{
					attackFlag = false;
				}
				if (!attackFlag)
				{
					animationCount = 0;
					count = playerSpriteFileName[myAnimationType][animLevelCount[myAnimationType]].size() - 1;
					notPushCount++;
					if (notPushCount >= 30)
					{
						animLevelCount[myAnimationType] = (AnimationLevel)(Level_None - 1);
						myAnimationType = Idle;
						notPushCount = 0;
					}
				}
			}
			animationID = animationTable[animationName][Animation_TB_Start] + count;
			//DrawFormatString(300, 300, 0xffffff, "count:%d", count);
			DrawFormatString(300, 300, 0xffffff, "attackFlag:%d", attackFlag);
		}
	}
	if (animationID < playerSpriteFileName[myAnimationType][animLevelCount[myAnimationType]].size())
	{
		switch (direction)
		{
		case Direction_Right:
			DrawRotaGraph(pos.x, pos.y, 1.0f, 0.0f,
						  lpSpriteMng.GetPlayerID(playerSpriteFileName,myAnimationType,animLevelCount[myAnimationType])[animationID],
						  true, false);
			break;

		case Direction_Left:
			DrawRotaGraph(pos.x, pos.y, 1.0f, 0.0f,
						  lpSpriteMng.GetPlayerID(playerSpriteFileName,myAnimationType, animLevelCount[myAnimationType])[animationID],
					      true, true);
			break;
		default:
			break;
		}
	}

	DrawFormatString(pos.x, pos.y - 150, 0xffffff, "animationID:%f", animationID);

	DrawFormatString(pos.x, pos.y - 100, 0xffffff, "myAnimationType:%d",myAnimationType);
	DrawFormatString(pos.x, pos.y - 180, 0xffffff, "animationLevel:%d", animLevelCount[myAnimationType]);
}

bool BasePlayer::AddAnimation(std::string animName, int frame, int interval, bool loop)
{
	animationTable[animName][Animation_TB_Start] = Animation_TB_Start;
	animationTable[animName][Animation_TB_Frame] = frame;
	animationTable[animName][Animation_TB_Interval] = interval;
	animationTable[animName][Animation_TB_Loop] = loop;
	return true;
}

bool BasePlayer::SetAnimation(std::string animName)
{
	if (BasePlayer::animationName == animName)
	{
		return true;
	}
	if (animationTable.find(animName) == animationTable.end())
	{
		return false;
	}
	BasePlayer::animationName = animName;
	BasePlayer::animationCount = 0;

	return false;
}

