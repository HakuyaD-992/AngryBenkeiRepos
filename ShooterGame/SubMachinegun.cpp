#include <DxLib.h>
#include "SoundManager.h"
#include "SubMachinegun.h"

SubMachinegun::SubMachinegun(Vector2I pos, int z, WeaponType type)
{
	pos_ = pos;
	z_ = z;
	type_ = type;
	canSetBulletType_ = BulletType::MachineBullet;
	name_ = "sub_machinegun";
	muzzleFlashName_ = "Bullets/muzzleflash_machine";
	muzzleFlashSize_ = Vector2I(13, 5);
	muzzleFlashDivCount_ = Vector2I(3, 2);
	havingBulletNum_ = MACHINEBULLETNUM;
	
	Initialize();
}

void SubMachinegun::UpDateAnimation(std::string animName)
{
	if (animName == "fire" || animName == "reload")
	{
		animationCount_ += 0.7f;
		if ((int)animationCount_ >= animMaxNum_[animName])
		{
			isAnimEnd_ = true;
		}
	}
	else
	{
		animationCount_ = 0.0f;
	}
	if (currentAnimation_ == "fire")
	{
		muzzleFlashAnimationCount_ += 0.15f;
		if (muzzleFlashAnimationCount_ >= 5)
		{
			muzzleFlashAnimationCount_ = 0.0f;
		}
	}

	if (isAnimEnd_)
	{
		animationCount_ = 0;
		//muzzleFlashAnimationCount_ = 0.0f;
	}
}

SubMachinegun::~SubMachinegun()
{
}

void SubMachinegun::UpDate(void)
{
	UpDateAnimation(currentAnimation_);

	if (isAnimEnd_)
	{
		SetAnimation("non");
	}
}
