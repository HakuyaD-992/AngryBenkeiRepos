#include <DxLib.h>

#include "WeaponBase.h"
#include "ImageManager.h"
#include "PlayerBullet.h"
#include "SoundManager.h"

WeaponBase::WeaponBase()
{
	// ±∆“∞ºÆ›Ç™èIóπÇµÇΩÃ◊∏ﬁ
	isAnimEnd_ = false;
	isTurnLeft_ = true;
	// ägëÂó¶
	exRate_ = 1.0f;
	// âÒì]ó¶
	rotRate_ = 0.0f;
	animationCount_ = 0.0f;
	muzzleFlashAnimationCount_ = 0.0f;
	currentAnimation_ = "non";
	drawPos_ = { 0,0 };
	isFire_ = false;
}

WeaponBase::~WeaponBase()
{
}

bool WeaponBase::Initialize(void)
{
	auto& imageMng = ImageManager::GetInstance();
	imageMng.LoadWeapon(type_, name_);
	imageMng.LoadDiv(muzzleFlashName_, muzzleFlashSize_, muzzleFlashDivCount_);
	for (auto resource : imageMng.GetWeaponResource(type_).actionNameSet_)
	{
		animMaxNum_.try_emplace(resource.first,resource.second.first.second-resource.second.first.first);
	}
	return true;
}

void WeaponBase::Draw(const bool& turnFlag)
{
	auto& imageMng = ImageManager::GetInstance();
	isTurnLeft_ = turnFlag;
	switch (type_)
	{
	case WeaponType::Pistol:

		if (isTurnLeft_)
		{
			drawPos_ = Vector2I(pos_.x - 5, pos_.y + (z_ / 2));

			muzzleFlashPos_ = Vector2I(drawPos_.x - 20, drawPos_.y - 5);
		}
		else
		{
			drawPos_ = Vector2I(pos_.x + 5, pos_.y + (z_ / 2));

			muzzleFlashPos_ = Vector2I(drawPos_.x + 20, drawPos_.y - 5);
		}
		break;

	case WeaponType::ShotGun:
		drawPos_ = Vector2I(pos_.x, pos_.y + (z_ / 2));

		if (isTurnLeft_)
		{
			muzzleFlashPos_ = Vector2I(drawPos_.x - 30, drawPos_.y);
		}
		else
		{
			muzzleFlashPos_ = Vector2I(drawPos_.x + 30, drawPos_.y);
		}
		break;
	case WeaponType::SubMachineGun:
		drawPos_ = Vector2I(pos_.x, pos_.y + (z_ / 2));

		if (turnFlag)
		{
			muzzleFlashPos_ = Vector2I(drawPos_.x - 30, drawPos_.y - 3);
		}
		else
		{
			muzzleFlashPos_ = Vector2I(drawPos_.x + 30, drawPos_.y - 3);
		}
		break;
	case WeaponType::Max:
		break;
	default:
		break;
	}

	// ïêäÌÇÃï`âÊ
	DrawRotaGraph(drawPos_.x,drawPos_.y,exRate_, rotRate_,
		imageMng.GetWeaponResource(type_).imageHandle_.find(currentAnimation_)->second[animationCount_],
		true, turnFlag);

	if (currentAnimation_ == "fire")
	{
		// èeå˚ÇÃâŒâ‘ÇÃï`âÊ
		DrawRotaGraph(muzzleFlashPos_.x, muzzleFlashPos_.y,
			1.0f, 0.0f, imageMng.GetDivID(muzzleFlashName_)[muzzleFlashAnimationCount_], true,
			turnFlag);
	}
}

void WeaponBase::SetPos(const Vector2I& pos, int z)
{
	pos_ = pos;
	z_ = z;
}

void WeaponBase::SetAnimation(std::string animName)
{
	isAnimEnd_ = false;
	currentAnimation_ = animName;
}

void WeaponBase::AddBullet(void)
{

	bullets_.emplace_back(std::make_shared<PlayerBullet>(pos_, z_, type_, isTurnLeft_));
}
