#include <DxLib.h>
#include "BulletBase.h"
#include "ImageManager.h"
#include "EnemyBullet.h"

BulletBase::BulletBase()
{
	isAnimEnd_ = false;
	isMoveLeft_ = false;
	deleteFlag_ = false;
	isShake_ = false;

	exRate_ = 1.0f;
	rotRate_ = 0.0f;
	speed_ = 0.0f;
	animationCount_ = 0.0f;
}

BulletBase::~BulletBase()
{
}

void BulletBase::Draw(void)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 80);
	DrawOvalAA(pos_.x, pos_.y + (z_ / 2) + (size_.y / 2), size_.x / 2, size_.y / 2, 10,
		0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);

}

bool BulletBase::Initialize(void)
{
	auto& imageMng = ImageManager::GetInstance();
	imageMng.LoadBullet(type_, bulletName_);
	auto imageResource = imageMng.GetBulletResource(type_);

	for (auto animSet : imageResource.actionNameSet_)
	{
		animationSet_.try_emplace(animSet.first, animSet.second.first.second - animSet.second.first.first);
		isLoop_.try_emplace(animSet.first, animSet.second.second);
	}

	return true;
}

void BulletBase::SetAnimation(std::string animName)
{
	if (currentAnimation_ == animName)
	{
		return;
	}
	if (animationSet_.find(animName) != animationSet_.end())
	{
		currentAnimation_ = animName;
		animationCount_ = 0;
		isAnimEnd_ = false;
	}
	else
	{
		animationCount_ = 0;
		isAnimEnd_ = true;
	}
}
