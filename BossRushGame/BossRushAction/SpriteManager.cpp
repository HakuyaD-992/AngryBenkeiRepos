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

const SpriteHandle& SpriteManager::GetID(std::string imageName)
{
	if (imageHandle.find(imageName) == imageHandle.end())
	{
		imageHandle[imageName].resize(1);
		imageHandle[imageName][0] = LoadGraph(imageName.c_str());
	}

	return imageHandle[imageName];
}

const SpriteHandle & SpriteManager::GetID(std::string imageName, const Vector2 & divSize, const Vector2 & divCount)
{
	if (imageHandle.find(imageName) == imageHandle.end())
	{
		imageHandle[imageName].resize(divCount.x * divCount.y);
		LoadDivGraph(imageName.c_str(), divCount.x*divCount.y,
					 divCount.x, divCount.y,
					 divSize.x, divSize.y, &imageHandle[imageName][0], true);
	}

	return imageHandle[imageName];
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

SpriteHandle SpriteManager::GetEnemyID(EnemyAnimSprite enemySpriteName, EnemyAnimation eAnim,const ENEMYTYPE& eType)
{
	if (enemySpriteMap[eAnim].find(eType) == enemySpriteMap[eAnim].end())
	{
		enemySpriteMap[eAnim][eType].resize(enemySpriteName[eAnim].size());
		for (int eSprite = 0; eSprite < enemySpriteName[eAnim].size(); eSprite++)
		{
			enemySpriteMap[eAnim][eType][eSprite] = LoadGraph(enemySpriteName[eAnim][eSprite].c_str());
		}
	}
	return enemySpriteMap[eAnim][eType];
}

void SpriteManager::SetPlayerAnimationString(std::array<std::string, Animation_Max> pAnimStrings)
{
	playerAnimationString = pAnimStrings;
}

void SpriteManager::SetEnemyAnimationString(std::array<std::string, Eanim_Max> eAnimStrings)
{
	enemyAnimationString = eAnimStrings;
}

void SpriteManager::SetPlayerSpriteName(PlayerSprite playerSpriteName)
{
	this->playerSpriteName = playerSpriteName;
}

void SpriteManager::SetEnemySpriteName(EnemySprite enemySpriteName)
{
	this->enemySpriteName = enemySpriteName;
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
