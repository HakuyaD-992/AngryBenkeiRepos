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
#define AttackRange 100

#define E_KnockBackFirstSP 70
#define E_KnockBackAccelSP 2

#define AttackedJumpFirstSpeed_Y -10

#define AttackedForce_Y 2

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
	Vector2 DistanceCalcurator(Vector2 objectPos);
	// find player
	bool IsHitObject(Vector2 distance,const Vector2& size);
	// can attack or not
	bool IsAttack(const Vector2& playerRectSize);

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

	// you can get far from player flag
	bool& GetIsFarest(void)
	{
		return isFarest;
	}

	int& GetHp(void)
	{
		return hp;
	}
	bool& Getdeleteflag(void)
	{
		return deleteFlag;
	}
	virtual void Delete(void)
	{
		deleteFlag = true;
	}

	const EnemyAnimation& GetmyAnimationType(void)
	{
		return myAnimationType;
	}
	// you can get attaaked jump flag
	bool& GetisAttackedJump(void)
	{
		return isAttackedJump;
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

	bool deleteFlag;


	unsigned int boxColliderColor;

	Vector2 hpbarPos;

protected:
	EnemyAnimSprite enemySpriteName;
	std::string typeName;

	// position
	Vector2 pos;
	Vector2 jumpMaxPos;
	Vector2 rectSize;
	Vector2 speed;

	// this value is additional value to "myFrame"
	int myFrameRate;
	int myFrame;
	// player's position
	Vector2 playerPos;
	Vector2 playerRectSize;
	// type of enemy
	ENEMYTYPE type;
	// animation types
	EnemyAnimation myAnimationType;
	// animation type before once
	EnemyAnimation oldAnimationType;

	ANIMATION playerAnimationType;
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
	Vector2 shotDistance;
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

	bool isBehind;
	// farest from player
	bool isFarest;

	int maxHP;
	bool deadFlag;
	// when enemy is attacked, enemy jump
	bool isAttackedJump;
	int attackedJumpFirstSpeed;
	int attackedJumpSpeed;
	int attackedForce;

	bool explosionFlag;

};

