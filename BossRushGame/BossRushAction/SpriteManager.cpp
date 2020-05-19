#include <DxLib.h>

#include "SpriteManager.h"


std::once_flag SpriteManager::onceflag;
SpriteManager* SpriteManager::spriteIns = nullptr;

void SpriteManager::Destroy(void)
{
	if (spriteIns != nullptr)
	{
		delete spriteIns;
	}
	spriteIns = nullptr;
}

SpriteHandle SpriteManager::GetPlayerID(PlayerSprite playerSpriteName,ANIMATION anim, AnimationLevel animlevel)
{
	if (playerSpriteMap[anim].find(animlevel) == playerSpriteMap[anim].end())
	{
		playerSpriteMap[anim][animlevel].resize(playerSpriteName[anim][animlevel].size());
		for (int pSprite = 0;pSprite < playerSpriteName[anim][animlevel].size();pSprite++)
		{
			playerSpriteMap[anim][animlevel][pSprite] = LoadGraph(playerSpriteName[anim][animlevel][pSprite].c_str());
		}
	}
	return playerSpriteMap[anim][animlevel];
}

void SpriteManager::SetPlayerAnimationString(std::array<std::string, Animation_Max> pAnimStrings)
{
	playerAnimationString = pAnimStrings;
}

//void SpriteManager::SetPlayterSpriteName(PlayerSprite playerSpriteName)
//{
//	this->playerSpriteName = playerSpriteName;
//}

SpriteManager::SpriteManager()
{
}


SpriteManager::~SpriteManager()
{
}

void SpriteManager::Create(void)
{
	spriteIns = new SpriteManager();
}
