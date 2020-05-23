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

#include "AddList.h"

// running speed
#define RunSpeed 2
// enemy's sight range
#define SightRange 350
// attack range
#define AttackRange 70

class BaseEnemy
{
public:
	BaseEnemy();
	~BaseEnemy();

	virtual void UpDate(WeakPlayerList playerList);
	virtual void Action(WeakPlayerList playerList) = 0;

	// draw player
	virtual void Draw(void);

	// add animation 
	bool AddAnimation(std::string animName, int frame, int interval, bool loop,ENEMYTYPE eType);
	// set animation
	bool SetAnimation(std::string animName,ENEMYTYPE eType);

	bool Init(EnemySprite enemySpriteName);

	// distance calcurator
	void DistanceCalcurator(Vector2 playerPos);
	// find player
	bool IsFindPlayer(void);
	// can attack or not
	bool IsAttack(void);
	// if distance will be minus, clamp this value
	void ClampDistance(Vector2& val);
	// enemy's direction changer
	void ChangeDirection(void);
private:

	EnemySprite enemySpriteName;
	// animation
	std::map<std::string, int[AnimationTB_Max]> animationTable[ETYPE_MAX];
	// animation name
	std::string animationName;
	// animation count integer
	int animationCount;
	// animation count
	int count;

protected:
	// position
	Vector2 pos;
	// type of enemy
	ENEMYTYPE type;
	// animation types
	EnemyAnimation myAnimationType;
	// direction
	DIRECTION direction;
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

	// distance
	Vector2 distance;
	// player is into enemy's sight range
	bool intoSightRangeFlag;
	// enemy's sight range
	int sightRange;
};

