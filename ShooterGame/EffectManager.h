#pragma once
#include <string>
#include <map>
#include <list>

#include "Geometory.h"

// ´Ìª¸Ä‚ğŠÇ—‚·‚é¸×½
// ¼İ¸ŞÙÄİ¸×½

#define lpEffect EffectManager::GetInstance()

class EffectManager
{
public:
	static EffectManager& GetInstance(void)
	{
		static EffectManager s_Instance;
		return s_Instance;
	}
	// XV
	void UpDate(void);
	// ´Ìª¸Ä‚Ì•`‰æ
	void Draw(void);
	// ‘S‚Ä‚Ì´Ìª¸Ä‚ÌÄ¶‚ğ~‚ß‚é
	bool StopAll(void);
	void SetPos(std::string effectName, const Vector2I& pos);
	// ´Ìª¸Ä‚ÌÄ¶
	bool Play(std::string effectName, const Vector2I& pos, std::string num = "");
	// effekseer‚Ì‰Šú‰»ŠÖ˜A
	bool Init(const Vector2I& size);

	void DeleteEffect(std::string effectName,const bool& flg);

	// ´Ìª¸Ä‚ªÄ¶’†‰Ø‚Ç‚¤‚©‚ÌÌ×¸Şæ“¾
	const int& IsPlayingEffect(std::string effectName);
	// ´Ìª¸Ä‚ÌÛ°ÄŞ
	void Load(std::string effectName);
private:
	EffectManager() = default;
	// ºËß°‹Ö~
	EffectManager(const EffectManager&) = delete;
	void operator=(const EffectManager&) = delete;
	// ÌßÚ²ÊİÄŞÙ‚Ìæ“¾
	const int& GetHandle(std::string effectName);

	// ´Ìª¸ÄÊİÄŞÙ
	std::map<std::string, int> handles_;
	// ÌßÚ²ÊİÄŞÙ‚ğŠi”[‚µ‚½Ø½Ä
	std::multimap<std::string,int> playList_;
	std::multimap<std::string, bool> delFlag_;
};


