#include <DxLib.h>
#include "Pistol.h"
#include "SoundManager.h"

Pistol::Pistol(Vector2I pos, int z, WeaponType type)
{
	pos_ = pos;
	z_ = z;
	type_ = type;
	reloadCnt_ = 0.0f;

	name_ = "pistol";
	canSetBulletType_ = BulletType::PistolBullet;

	havingBulletNum_ = PISTOLBULLETNUM;
	muzzleFlashName_ = "Bullets/muzzleflash_pistol";
	muzzleFlashSize_ = Vector2I(8, 5);
	muzzleFlashDivCount_ = Vector2I(3, 1);
	Initialize();
}

Pistol::~Pistol()
{
}

void Pistol::UpDateAnimation(std::string animName)
{
	if (animName == "fire")
	{
		animationCount_ += 0.35f;
		muzzleFlashAnimationCount_ += 0.25f;
		if (muzzleFlashAnimationCount_ >= 3.0f)
		{
			isAnimEnd_ = true;
		}
		if ((int)animationCount_ >= animMaxNum_[animName] - 1)
		{
			animationCount_ = animMaxNum_[animName] - 1;
		}
	}

	if (isAnimEnd_)
	{
		animationCount_ = 0;
		muzzleFlashAnimationCount_ = 0.0f;
	}
}

void Pistol::UpDate(void)
{
	UpDateAnimation(currentAnimation_);

	if (currentAnimation_ == "fire")
	{
	}

	if (currentAnimation_ == "reload")
	{
		reloadCnt_ += 0.5f;
		if (reloadCnt_ >= 5.0f)
		{
			reloadCnt_ = 0.0f;
			isAnimEnd_ = true;
		}
		if (isTurnLeft_)
		{
			rotRate_+=0.08f;
		}
		else
		{
			rotRate_-=0.08f;
		}
	}

	if (isAnimEnd_)
	{
		rotRate_ = 0.0f;
		SetAnimation("non");
	}
}
