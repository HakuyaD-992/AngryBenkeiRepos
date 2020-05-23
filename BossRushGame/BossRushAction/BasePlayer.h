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

class GameController;

class BasePlayer
{
public:
	BasePlayer();
	~BasePlayer();
	// update player
	virtual void UpDate(const GameController& gameCtl);
	// initialize player
	virtual bool Init(PlayerSprite playerSpriteName, std::array<AnimationLevel, Animation_Max> animLevel);
	// draw player
	virtual void Draw(void);

	// add animation
	bool AddAnimation(std::string animName, int frame, int interval, bool loop);
	// set animation
	bool SetAnimation(std::string animName);
	// you can get player's position
	const Vector2& GetPos(void)
	{
		return pos;
	}

private:
	// player's action
	virtual void Action(const GameController& gameCtl) = 0;

	PlayerSprite playerSpriteFileName;
	// animation
	std::map<std::string, int[AnimationTB_Max]> animationTable;
	// animation name
	std::string animationName;
	// animation count integer
	int animationCount;
	// animation count
	int count;

protected:
	// my position
	Vector2 pos;
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
};

