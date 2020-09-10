#include <DxLib.h>
#include "SoundManager.h"

SoundManager* SoundManager::s_Instance = nullptr;

void SoundManager::Load(std::string soundName, bool loop)
{
	handles_.try_emplace(soundName,
		std::make_pair(LoadSoundMem(("Sound/" + soundName + ".mp3").c_str()), loop));
}

bool SoundManager::Play(std::string soundName,int playType)
{
	if (CheckSoundMem(handles_[soundName].first == 0))
	{
		PlaySoundMem(handles_[soundName].first, playType, handles_[soundName].second);
	}
	return false;
}

void SoundManager::Stop(std::string soundName)
{
	StopSoundMem(handles_[soundName].first);
}

void SoundManager::ChangeVolume(std::string soundName, int vol)
{
	ChangeVolumeSoundMem(vol, handles_[soundName].first);
}
