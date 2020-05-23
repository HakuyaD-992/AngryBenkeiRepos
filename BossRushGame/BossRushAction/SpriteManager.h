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
	// you can get player sprite ID
	SpriteHandle GetEnemyID(EnemyAnimSprite enemySpriteName,EnemyAnimation eAnim);
	
	void SetPlayerAnimationString(std::array<std::string, Animation_Max> pAnimStrings);
	void SetEnemyAnimationString(std::array<std::string, Eanim_Max> eAnimStrings);

	void SetPlayerSpriteName(PlayerSprite playerSpriteName);
	void SetEnemySpriteName(EnemySprite enemySpriteName);


	// you can get player's animation string
	std::string GetPlayerAnimationString(ANIMATION anim)
	{
		return playerAnimationString[anim];
	}
	// you can get enemy's animation string
	std::string GetEnemyAnimationString(EnemyAnimation eAnim)
	{
		return enemyAnimationString[eAnim];
	}
	// you can get player's sprite name
	const PlayerSprite& GetPlayerSpriteName(void)
	{
		return playerSpriteName;
	}
	// you can get enemy's sprite name
	const EnemySprite& GetEnemySpriteName(void)
	{
		return enemySpriteName;
	}

private:
	SpriteManager();
	~SpriteManager();

	static std::once_flag onceflag;
	static SpriteManager* spriteIns;

	PlayerSprite playerSpriteName;
	EnemySprite enemySpriteName;

	// player's animations string
	std::array<std::string, Animation_Max> playerAnimationString;
	// enemy's animations string
	std::array<std::string, Eanim_Max> enemyAnimationString;

	static void Create(void);

	// player's sprite handle
	std::map<AnimationLevel,SpriteHandle> playerSpriteMap[Animation_Max];
	// enemy's sprite handle
	std::map<EnemyAnimation, SpriteHandle> enemySpriteMap;
};

