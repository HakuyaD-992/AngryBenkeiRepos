#pragma once
#include <map>
#include <array>
#include <vector>

#include "Vector2.h"
#include "ENEMYTYPE.h"
#include "ANIMATIONTABLE.h"
#include "DIRECTION.h"
#include "EnemyAnimation.h"
#include "GamePlay.h"
#include "Gravity.h"
#include "Collider.h"

#include "AddList.h"

// running speed
#define RunSpeed 2
// enemy's sight range
#define SightRange 120
// attack range
#define AttackRange 70

#define E_KnockBackFirstSP 30
#define E_KnockBackAccelSP 2

#define MAXHP 30

class BaseEnemy
{
public:
	BaseEnemy();
	~BaseEnemy();

	virtual void UpDate(WeakPlayerList playerList);
	virtual void Action(WeakPlayerList playerList) = 0;

	// draw enemy
	virtual void Draw(void);
	// draw box collider
	void DrawBoxCollider(void);

	// add animation 
	bool AddAnimation(std::string animName, int frame, int interval, bool loop,ENEMYTYPE eType);
	// set animation
	bool SetAnimation(std::string animName,ENEMYTYPE eType);

	void SetCollider(const EnemyRectData& enemyCollider);

	bool Init(const EnemyAnimSprite& enemySpriteName);

	// distance calcurator
	void DistanceCalcurator(Vector2 playerPos);
	// find player
	bool IsFindPlayer(void);
	// can attack or not
	bool IsAttack(void);

	bool IsHitPlayerAttack(const ActionRect& playerRect);
	// if distance will be minus, clamp this value
	void ClampDistance(Vector2& val);
	// enemy's direction changer
	void ChangeDirection(void);
	// you can get enemy position
	const Vector2& GetPos(void)
	{
		return pos;
	}

	const DIRECTION& GetDirection(void)
	{
		return direction;
	}

	// you can get damage flag
	const bool& GetDamageFlag(void)
	{
		return damageFlag;
	}
	// you can get hit flag
	const bool& GetHitFlag(void)
	{
		return hitFlag;
	}

	const bool& GetHitAttack(void)
	{
		return isHitAttack;
	}
	const ENEMYTYPE& GetType(void)
	{
		return type;
	}

private:

	// animation
	std::map<std::string, int[AnimationTB_Max]> animationTable[ETYPE_MAX];
	// animation name
	std::string animationName;
	// animation count integer
	int animationCount;
	// animation count
	int count;


	unsigned int boxColliderColor;


protected:
	EnemyAnimSprite enemySpriteName;

	// position
	Vector2 pos;
	Vector2 speed;
	// player's position
	Vector2 playerPos;
	// type of enemy
	ENEMYTYPE type;
	// animation types
	EnemyAnimation myAnimationType;
	// animation type before once
	EnemyAnimation oldAnimationType;
	// direction
	DIRECTION direction;
	// gravity
	Gravity* gravity;

	// flag whether player stand floor or not
	bool onFloor;

	// animationID
	int animationID;

	// flag of jump
	bool isJump;
	// first speed of jump
	float startingJumpForce;
	// jump force
	Vector2 jumpForce;

	// enemy's attack flag
	bool attackFlag;
	// hit player's attack
	bool hitFlag;
	// hit enemy's attack flag
	bool isHitAttack;

	// enemy's damage flag
	bool damageFlag;

	// distance
	Vector2 distance;
	// player is into enemy's sight range
	bool intoSightRangeFlag;
	// enemy's sight range
	int sightRange;

	EnemyAnimationRectData collider;

	// enemy's hp
	int hp;

	// knock back
	bool knockBackFlag;
	int kbFirstSpeed;
	int kbAccel;
	int kbSpeed;
};

