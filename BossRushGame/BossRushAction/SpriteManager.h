#pragma once
#include <mutex>
#include <map>
#include <vector>

#include "ANIMATION.h"
#include "AnimationLevel.h"
#include "PLAYER.h"
#include "GamePlay.h"

using SpriteHandle = std::vector<int>;

#define lpSpriteMng SpriteManager::getInstance()

class SpriteManager
{
public:
	static void Destroy(void);
	static SpriteManager &getInstance(void)
	{
		std::call_once(onceflag, Create);
		return *spriteIns;
	}

	// you can get player sprite ID
	SpriteHandle GetPlayerID(PlayerSprite playerSpriteName,ANIMATION anim, AnimationLevel animlevel);
	
	void SetPlayerAnimationString(std::array<std::string, Animation_Max> pAnimStrings);
	//void SetPlayterSpriteName(PlayerSprite playerSpriteName);
	std::string GetPlayerAnimationString(ANIMATION anim)
	{
		return playerAnimationString[anim];
	}

private:
	SpriteManager();
	~SpriteManager();

	static std::once_flag onceflag;
	static SpriteManager* spriteIns;

	//PlayerSprite playerSpriteName;

	// player animations string
	std::array<std::string, Animation_Max> playerAnimationString;


	static void Create(void);

	std::map<AnimationLevel,SpriteHandle> playerSpriteMap[Animation_Max];
};

