#pragma once
#include <vector>
#include <string>
#include <array>
#include <map>

#include "Vector2.h"
#include "GamePlay.h"

#include "Gravity.h"
#include "ANIMATION.h"
#include "DIRECTION.h"
#include "ANIMATIONTABLE.h"
#include "AnimationLevel.h"
#include "Collider.h"
#include "AddList.h"
#include "BaseEnemy.h"

#define MAXHP 30
#define P_KnockBackFirstSP 5.0f
#define P_KnockBackAccelSP 0.3f

class GameController;
class Camera;

class BasePlayer
{
public:
	BasePlayer();
	~BasePlayer();
	// update player
	virtual void UpDate(const GameController& gameCtl,WeakEnemyList enemyList);
	// initialize player
	virtual bool Init(PlayerSprite playerSpriteName, 
					  const Actor& actor);
	// draw player
	virtual void Draw(void);
	void SetCollider(const PlayerRectData& playerCollider);

	// add animation
	bool AddAnimation(std::string animName, int frame, int interval, bool loop);
	// set animation
	bool SetAnimation(std::string animName);
	// you can get player's position
	const Vector2& GetPos(void)
	{
		return pos;
	}
	// you can get direction
	const DIRECTION& GetDirection(void)
	{
		return direction;
	}

	bool IsHitEnemyAttack(const ActionRect& enemyRect);
	// if distance will be minus, clamp this value
	void ClampDistance(Vector2& val);

	// you can get animation type
	const ANIMATION& GetMyAnimationType(void)
	{
		return myAnimationType;
	}
	// you can get animation string
	const std::string GetAnimationString(const ANIMATION& anim)
	{
		return animString[anim];
	}

	// you can get animation level count
	const AnimationLevel& GetAnimationLevelCount(const ANIMATION& anim)
	{
		return animLevelCount[anim];
	}
	// you can animation level max num
	const AnimationLevel& GetAnimationLevelMaxNum(const ANIMATION& anim)
	{
		return animLevel[anim];
	}
	// you can get knockback flag
	const bool& GetKnockbackFlag(void)
	{
		return knockbackFlag;
	}

	//bool IsEnemyBack(const Vector2& enemyPos);


private:
	// player's action
	virtual void Action(const GameController& gameCtl,WeakEnemyList enemyList) = 0;
	// draw collider
	void DrawBoxCollider(void);

	PlayerSprite playerSpriteFileName;
	// animation
	std::map<std::string, int[AnimationTB_Max]> animationTable;
	// animation name
	std::string animationName;
	// animation count integer
	int animationCount;
	// animation count
	int count;

	AnimationLevel nextlevel;

	unsigned int boxColliderColor;

	//// whether enemy is back of player or not
	//bool backFlag;
protected:

	int animationID;
	// my position
	Vector2 pos;

	// floor
	Vector2 floorPos;
	// player's direction
	DIRECTION direction;
	// my animation
	ANIMATION myAnimationType;
	// old my animation
	ANIMATION oldAnimationType;
	// level of animation
	std::array<AnimationLevel,Animation_Max> animLevel;
	// old animation level count
	int oldLevel;
	// level count integer
	std::array<AnimationLevel, Animation_Max> animLevelCount;
	// animation string
	std::array<std::string, Animation_Max> animString;

	// gravity
	Gravity* gravity;

	// flag whether player stand floor or not
	bool onFloor;

	// flag of jump
	bool isJump;
	// first speed of jump
	float startingJumpForce;
	// jump force
	Vector2 jumpForce;

	// player's attack flag
	bool attackFlag;
	// you dont push "attack key", this count increasing
	int notPushCount;
	// collider
	PlayerRectData collider;

	// hit player's attack flag
	bool isHitAttack;

	// damage
	bool damageFlag;
	// damage count
	int damageCount;
	// knock back flag
	bool knockbackFlag;
	bool getupFlag;

	float kbFirstSpeed;
	float kbAccel;
	float kbSpeed;

	// hit
	bool hitFlag;

	int hp;
};

