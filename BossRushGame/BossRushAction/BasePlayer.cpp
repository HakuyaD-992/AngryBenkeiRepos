#include <DxLib.h>

#include "BasePlayer.h"
#include "SpriteManager.h"
#include "Collider.h"
#include "Camera.h"
#include "SoundManager.h"


BasePlayer::BasePlayer()
{
	// initialize animation level count
	animLevelCount = {
		Level_None,
		Level_None,
		Level_None,
		Level_None,
		Level_None,
		Level_None,
		Level_None,
		Level_None,
		Level_None,
		Level_None,
		Level_None
	};
	//instance gravity
	gravity = new Gravity();

	onFloor = false;

	isJump = false;
	startingJumpForce = -10.0f;
	jumpForce = { 0,0 };

	attackFlag = false;
	isHitAttack = false;
	notPushCount = 0;

	damageFlag = false;
	knockbackFlag = false;
	getupFlag = false;
	hitFlag = false;
	hp = MAXHP;

	//backFlag = false;

	kbAccel = 0.0f;
	kbFirstSpeed = P_KnockBackFirstSP;
	kbSpeed = 0.0f;
}


BasePlayer::~BasePlayer()
{
}

void BasePlayer::UpDate(const GameController & gameCtl, WeakEnemyList enemyList)
{
	if (!isJump && !onFloor)
	{
		gravity->PutGravityOnActor(pos);
	}

	Action(gameCtl,enemyList);
}

bool BasePlayer::Init(PlayerSprite playerSpriteName,
					  const Actor& actor)
{
	playerSpriteFileName = playerSpriteName;
	this->animLevel = actor.animationLevel;
	animString = actor.animationString;
	return true;
}

void BasePlayer::DrawBoxCollider(void)
{
	auto tmpColliderBox = collider[myAnimationType].playerAnimLevelData[animLevelCount[myAnimationType]].playerRectData[animationID];

	for (int flag = R_State_Damage; flag < R_State_Max; flag++)
	{
		for (int colliderNum = 0; colliderNum < tmpColliderBox.rectNum[flag];colliderNum++)
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

//bool BasePlayer::IsEnemyBack(const Vector2& enemyPos)
//{
//	switch (direction)
//	{
//	case Direction_Right:
//		if (pos.x - 75 > enemyPos.x)
//		{
//			backFlag = true;
//		}
//		else
//		{
//			backFlag = false;
//		}
//
//		break;
//	case Direction_Left:
//		if (pos.x + 75 < enemyPos.x)
//		{
//			backFlag = true;
//		}
//		else
//		{
//			backFlag = false;
//		}
//		break;
//	default:
//		break;
//	}
//	return backFlag;
//}

void BasePlayer::Draw(void)
{
	if (playerSpriteFileName[myAnimationType][animLevelCount[myAnimationType]].size() - 1 == 0)
	{
		return;
	}

	animationID = 0;

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
					count %= animationTable[animationName][Animation_TB_Frame];
				}
				else
				{
					// Ù°ÌßÄ¶Ì×¸Þ‚ªfalse‚Ìê‡‚Í1±ÆÒ°¼®Ý‚ªI‚í‚èŽŸ‘æ‘Ò‚¿Ó°¼®Ý‚É‚·‚é
					//myActionType = ANIM_WAIT;
					count = animationTable[animationName][Animation_TB_Frame]
						/ (playerSpriteFileName[myAnimationType][animLevelCount[myAnimationType]].size());
				}
				
				if (count >= playerSpriteFileName[myAnimationType][animLevelCount[myAnimationType]].size() - 1)
				{
					if (!knockbackFlag)
					{
						hitFlag = false;
						attackFlag = false;
					}
					else
					{
						knockbackFlag = false;
						count = playerSpriteFileName[myAnimationType][animLevelCount[myAnimationType]].size() - 1;
					}
				}
			}
			else 
			{
				
				// push attack key
				if (attackFlag)
				{
					animationCount++;
					count = (animationCount / (animationTable[animationName][Animation_TB_Interval]));
					
				}
				else
				{
					animationCount = 0;
					count = 0;
				}
				// “–‚½‚Á‚½‚çÚÍÞÙ‚ðã‚°‚é
				if (isHitAttack)
				{
					nextlevel = (AnimationLevel)(animLevelCount[myAnimationType] + 1);
				}
				if (nextlevel >= animLevel[myAnimationType])
				{
					nextlevel = Level_None;
				}
				if (count >= playerSpriteFileName[myAnimationType][animLevelCount[myAnimationType]].size())
				{
					animLevelCount[myAnimationType] = nextlevel;

					count = 0;
					attackFlag = false;
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
		DrawBoxCollider();
	}
	
	DrawFormatString(pos.x, pos.y - 150, 0xffffff, "animationID:%d", animationID);

	DrawFormatString(pos.x, pos.y - 100, 0xffffff, "myAnimationType:%d",myAnimationType);
	DrawFormatString(pos.x, pos.y - 180, 0xffffff, "animationLevel:%d", animLevelCount[myAnimationType]);
}

void BasePlayer::SetCollider(const PlayerRectData& playerCollider)
{
	this->collider = playerCollider;
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

bool BasePlayer::IsHitEnemyAttack(const ActionRect & enemyRect)
{
	if (!hitFlag)
	{
		Vector2 e_distance;
		auto attackRect = enemyRect;
		auto damageRect = collider[myAnimationType].playerAnimLevelData[animLevelCount[myAnimationType]].playerRectData[animationID];
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

void BasePlayer::ClampDistance(Vector2& val)
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