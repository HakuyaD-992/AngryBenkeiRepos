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

void ImageManager::SetAnimationName(const ANIMATION & anim,const WEAPON& weapon,FileName fileName)
{
	for (auto file = fileName.begin(); file != fileName.end(); file++)
	{
		animationImageName[weapon][anim].push_back((*file));
	}
}

void ImageManager::SetAnimationString(const Actor & actor,const ANIMATION & anim)
{
	animString[anim] = actor.animationName[anim];
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

const VecInt & ImageManager::GetCombinedID(const ANIMATION & anim,const WEAPON& weapon)
{
	if (playerHandleMap[weapon].find(anim) == playerHandleMap[weapon].end())
	{
		for (auto p = animationImageName[weapon][anim].begin(); p != animationImageName[weapon][anim].end(); p++)
		{
			playerHandleMap[weapon][anim].push_back(LoadGraph((*p).c_str()));
		}
	}
	return playerHandleMap[weapon][anim];
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
