#pragma once
#include <mutex>
#include <vector>
#include <array>
#include <map>

#include "ANIMATION.h"
#include"AnimationLevel.h"
#include "EnemyAnimation.h"
#include "ENEMYTYPE.h"
#include "GamePlay.h"

#define lpSoundMng SoundManager::getInstance()

using SoundHandle = std::vector<int>;

class SoundManager
{
public:
	static void Destroy(void);
	static SoundManager &getInstance(void)
	{
		Create();
		return *soundIns;
	}

	const SoundHandle GetSoundID(std::string soundName);
	
	const SoundHandle GetPlayerSoundID(std::string animName,
									   const ANIMATION& pAnimation,
									   const AnimationLevel& animlevel);

	const SoundHandle GetEnemySoundID(std::string soundName,
									  std::string typeName,
									  const ENEMYTYPE& eType,
									  EnemyAnimation& eAnimation);

	const SoundHandle GetPlayerSoundEffectID(std::string soundName, const AnimationLevel& animlevel);

private:
	SoundManager();
	~SoundManager();

	static std::once_flag onceflag;
	static SoundManager* soundIns;

	static void Create(void);

	std::map<std::string, SoundHandle> soundHandle;

	std::map<std::string, SoundHandle> playerSoundEffectHandle[Level_Max];

	// player's sound handle
	std::map<AnimationLevel, SoundHandle> playerSoundHandle[Animation_Max];
	// enemy's sound handle
	std::map<EnemyAnimation, SoundHandle> enemySoundHandle[ETYPE_MAX];
};

