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
		Level_None,
		Level_None,
	};

	isHitEnemyType = ETYPE_MAX;
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

	animInitFlag = false;
	backFlag = false;
	attackJumpFlag = false;

	kbAccel = 0.0f;
	kbFirstSpeed = P_KnockBackFirstSP;
	kbSpeed = 0.0f;

	gaugeCount = 0;

	attackMotionFlag = false;
	shotFlag = false;
	shotIntervalCount = 0;
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

void BasePlayer::AnimInit(void)
{
	for (int anim = Idle; anim < Animation_Max; anim++)
	{
		animLevelCount[(ANIMATION)anim] = Level_None;
	}
	cannextAttackFlag = false;
	for (int i = 0; i < 2; i++)
	{
		nextAttackFlag[i] = false;
	}
}

void BasePlayer::DrawSuperAttackGauge(void)
{
	DrawRotaGraph(300, 70, 1.0f, 0.0f,
				  lpSpriteMng.GetID("Image/GamePlay/superAttackGauge.png")[0],
				  true, false);

	DrawExtendGraph(225, 59, 225 + gaugeCount, 81,
		lpSpriteMng.GetID("Image/GamePlay/meter.png")[0],
		true);

}

bool BasePlayer::CheckBehind(const Vector2& enemyPos)
{
	switch (direction)
	{
	case Direction_Right:
		if (pos.x > enemyPos.x)
		{
			backFlag = true;
		}
		else
		{
			backFlag = false;
		}

		break;
	case Direction_Left:
		if (pos.x + 75 < enemyPos.x)
		{
			backFlag = true;
		}
		else
		{
			backFlag = false;
		}
		break;
	default:
		break;
	}
	return backFlag;
}

void BasePlayer::Draw(void)
{
	if (playerSpriteFileName[myAnimationType][animLevelCount[myAnimationType]].size() - 1 == 0)
	{
		return;
	}

	animationID = 0;

	if (animInitFlag)
	{
		AnimInit();
	}

	if (animationTable.find(animationName) != animationTable.end())
	{

		{
			if (!attackMotionFlag)
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
				if (myAnimationType == Attack || myAnimationType == Attack_Sword)
				{
					if (isHitAttack)
					{
						nextlevel = (AnimationLevel)(animLevelCount[myAnimationType] + 1);
					}
				}
				else
				{
					nextlevel = Level_None;
				}

				if (nextlevel > animLevel[myAnimationType] - 1)
				{

					cannextAttackFlag = true;
					nextlevel = Level_None;
	
					cannextAttackFlag = false;
					for (int i = 0; i < 2; i++)
					{
						nextAttackFlag[i] = false;
					}
				}
				if (count >= playerSpriteFileName[myAnimationType][animLevelCount[myAnimationType]].size())
				{
					animLevelCount[myAnimationType] = nextlevel;
					animationCount = 0;
					count = 0;
					attackFlag = false;
				}
			}
			if (myAnimationType != oldAnimationType)
			{
				animationID = 0;
				count = 0;
			}
			
			animationID = animationTable[animationName][Animation_TB_Start] + count;
			DrawFormatString(300, 300, 0xffffff, "count:%d", count);
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
	//DrawSuperAttackGauge();
	//DrawFormatString(pos.x, pos.y - 150, 0xffffff, "nextAttackFlag:%d", cannextAttackFlag);

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

void BasePlayer::DistanceCalcurator(Vector2 enemyPos)
{
	distance = enemyPos - pos;
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