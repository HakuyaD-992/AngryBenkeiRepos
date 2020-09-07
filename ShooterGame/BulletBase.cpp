
#include "BulletBase.h"
#include "ImageManager.h"

BulletBase::BulletBase()
{
	isAnimEnd_ = false;
	isMoveLeft_ = false;
	deleteFlag_ = false;

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
}

void BulletBase::SetAnimation(std::string animName)
{
	isAnimEnd_ = false;
	currentAnimation_ = animName;
}
