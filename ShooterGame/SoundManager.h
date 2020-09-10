#pragma once
#include <map>
#include <string>

#include "Wave.h"

// ‰¹ŠÇ—‚Ì¼İ¸ŞÙÄİ¸×½
#define lpSound SoundManager::GetInstance()

class SoundManager
{
public:
	static SoundManager& GetInstance(void)
	{
		Create();
		return *s_Instance;
	}
	static void Create(void)
	{
		if (s_Instance == nullptr)
		{
			s_Instance = new SoundManager();
		}
	}

	void Destroy(void)
	{
		if (s_Instance != nullptr)
		{
			delete s_Instance;
		}
		s_Instance = nullptr;
	}
	void Load(std::string soundName, bool loop);

	bool Play(std::string soundName,int playType);
	void Stop(std::string soundName);

	void ChangeVolume(std::string soundName, int vol);

	const int& GetHandle(std::string soundName)
	{
		return handles_[soundName].first;
	}
private:
	SoundManager() = default;
	SoundManager(const SoundManager&) = delete;
	void operator=(const SoundManager&) = delete;

	static SoundManager* s_Instance;

	std::map<std::string, std::pair<int, bool>> handles_;
};

