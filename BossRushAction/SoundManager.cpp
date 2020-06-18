#include <DxLib.h>

#include "SoundManager.h"

std::once_flag SoundManager::onceflag;
SoundManager* SoundManager::soundIns = nullptr;

void SoundManager::Destroy(void)
{
	if (soundIns != nullptr)
	{
		delete soundIns;
	}
	soundIns = nullptr;
}


const SoundHandle SoundManager::GetSoundID(std::string soundName)
{
	if (soundHandle.find(soundName) == soundHandle.end())
	{
		std::string soundString = "Sound/" + soundName + ".mp3";
		soundHandle[soundName].resize(1);
		soundHandle[soundName][0] = LoadSoundMem(soundString.c_str());
	}
	return soundHandle[soundName];
}

const SoundHandle SoundManager::GetPlayerSoundID(std::string animName, const ANIMATION & pAnimation, const AnimationLevel & animlevel)
{
	if (playerSoundHandle[pAnimation].find(animlevel) == playerSoundHandle[pAnimation].end())
	{
		playerSoundHandle[pAnimation][animlevel].resize(1);
		std::string soundHandleName = "Sound/Player/" + animName + "/" + animName + std::to_string(animlevel + 1) + ".mp3";
		playerSoundHandle[pAnimation][animlevel][0] = LoadSoundMem(soundHandleName.c_str());
	}

	return playerSoundHandle[pAnimation][animlevel];
}

const SoundHandle SoundManager::GetEnemySoundID(std::string soundName,std::string typeName, const ENEMYTYPE & eType, EnemyAnimation & eAnimation)
{
	if (enemySoundHandle[eType].find(eAnimation) == enemySoundHandle[eType].end())
	{
		std::string enemySoundFileName
			= "Sound/Enemy/" + typeName + "/" + soundName + ".mp3";

		enemySoundHandle[eType][eAnimation].resize(1);
		enemySoundHandle[eType][eAnimation][0] = LoadSoundMem(enemySoundFileName.c_str());
	}

	return enemySoundHandle[eType][eAnimation];
}

const SoundHandle SoundManager::GetPlayerSoundEffectID(std::string soundName, const AnimationLevel& animlevel)
{
	if (playerSoundEffectHandle[animlevel].find(soundName) == playerSoundEffectHandle[animlevel].end())
	{
		std::string soundFileName = "Sound/Player/effectSe/" + soundName + "/" + soundName + std::to_string(animlevel + 1) + ".mp3";

		playerSoundEffectHandle[animlevel][soundName].resize(1);
		playerSoundEffectHandle[animlevel][soundName][0] = LoadSoundMem(soundFileName.c_str());
	}
	return playerSoundEffectHandle[animlevel][soundName];
}

SoundManager::SoundManager()
{
}


SoundManager::~SoundManager()
{
}

void SoundManager::Create(void)
{
	if (soundIns == nullptr)
	{
		soundIns = new SoundManager();
	}
}
