#include "AK69.h"
#include "ImageManager.h"
#include "PlayerBullet.h"

AK69::AK69(Vector2I pos, int z, WeaponType type)
{
	pos_ = pos;
	z_ = z;
	type_ = type;
	name_ = "shotgun";
	canSetBulletType_ = BulletType::ShotBullet;

	muzzleFlashName_ = "Bullets/muzzleflash_shot";
	muzzleFlashSize_ = Vector2I(20, 33);
	muzzleFlashDivCount_ = Vector2I(3, 2);
	havingBulletNum_ = SHOTBULLETNUM;
	Initialize();
}

AK69::~AK69()
{
}

void AK69::UpDate(void)
{
	//if (currentAnimation_ == "reload")
	//{
	//	if (isTurnLeft_)
	//	{
	//		rotRate_ = 45.0f;
	//	}
	//	else
	//	{
	//		rotRate_ = -45.0f;
	//	}
	//}

	if (currentAnimation_ == "fire")
	{
		if (isTurnLeft_)
		{
			rotRate_ = animationCount_ * 0.2f;
		}
		else
		{
			rotRate_ = -animationCount_ * 0.2f;
		}
	}
	UpDateAnimation(currentAnimation_);

	if (isAnimEnd_)
	{
		rotRate_ = 0.0f;
		SetAnimation("non");
	}
}

void AK69::UpDateAnimation(std::string animName)
{
	if (animName == "fire")
	{
		animationCount_ += 0.15f;
		if ((int)animationCount_ >= animMaxNum_[animName] - 1)
		{
			animationCount_ = animMaxNum_[animName] - 1;
		}
	}
	//if (currentAnimation_ == "reload")
	//{
	//	animationCount_ += 0.35f;
	//	if ((int)animationCount_ >= animMaxNum_[animName] - 1)
	//	{
	//		isAnimEnd_ = true;
	//	}
	//}

	if (currentAnimation_ == "fire")
	{
		muzzleFlashAnimationCount_ += 0.25f;
		if (muzzleFlashAnimationCount_ >= 6.0f)
		{
			isAnimEnd_ = true;
		}
	}

	if (isAnimEnd_)
	{
		animationCount_ = 0;
		muzzleFlashAnimationCount_ = 0.0f;
	}
}
