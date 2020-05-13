#include "DxLib.h"

#include "ImageManager.h"

std::once_flag ImageManager::onceflag;
ImageManager* ImageManager::imageIns = nullptr;

void ImageManager::Destroy(void)
{
	if (imageIns != nullptr)
	{
		delete imageIns;
	}
	imageIns = nullptr;
}

void ImageManager::SetAnimationName(const ANIMATION & anim,const WEAPON& weapon,WeaponFile fileName,ATTACK_LEVEL& level)
{
	animationImageName[anim][weapon] = fileName;

	level = (ATTACK_LEVEL)animationImageName[anim][weapon].size();
}

void ImageManager::SetAnimationString(const std::string animationName,const PLAYER& player,const ANIMATION & anim)
{
	animString[player][anim] = animationName;
}


void ImageManager::SetAnimationName(const ANIMATION & anim, const EnemyType& type, FileName file)
{
	if (enemyImageName[type][anim].size() <= 0 && file.size() > 0)
	{
		enemyImageName[type][anim] = file;
	}
}

const VecInt & ImageManager::GetID(std::string imageName)
{
	if (imageHandleMap.find(imageName) == imageHandleMap.end())
	{
		imageHandleMap[imageName].resize(1);
		imageHandleMap[imageName][0] = LoadGraph(imageName.c_str());
	}
	return imageHandleMap[imageName];
}

const VecInt & ImageManager::GetID(std::string imageName, Vector2 divSize, Vector2 divCount)
{
	if (imageHandleMap.find(imageName) == imageHandleMap.end())
	{
		imageHandleMap[imageName].resize(divCount.x * divCount.y);
		LoadDivGraph(imageName.c_str(),
					 divCount.x * divCount.y,
					 divCount.x, divCount.y,
					 divSize.x, divSize.y,
					 &imageHandleMap[imageName][0]);
	}
	return imageHandleMap[imageName];
}

const VecInt & ImageManager::GetCombinedID(const ANIMATION & anim,const WEAPON& weapon,const int& level)
{
	if (playerHandleMap[weapon][anim].find((ATTACK_LEVEL)level) == playerHandleMap[weapon][anim].end())
	{
		for (auto p = animationImageName[anim][weapon][level].begin(); p != animationImageName[anim][weapon][level].end(); p++)
		{
			playerHandleMap[weapon][anim][(ATTACK_LEVEL)level].push_back(LoadGraph((*p).c_str()));
		}
	}
	return playerHandleMap[weapon][anim][(ATTACK_LEVEL)level];
}

const VecInt & ImageManager::GetCombinedID(const ANIMATION & anim, const EnemyType& type)
{
	if (enemyHandleMap[type].find(anim) == enemyHandleMap[type].end())
	{
		for (auto e = enemyImageName[type][anim].begin(); e != enemyImageName[type][anim].end(); e++)
		{
			enemyHandleMap[type][anim].push_back(LoadGraph((*e).c_str()));
		}
	}
	return enemyHandleMap[type][anim];
}

ImageManager::ImageManager()
{
}


ImageManager::~ImageManager()
{
}

void ImageManager::Create(void)
{
	imageIns = new ImageManager();
}
