#include <DxLib.h>
#include "Actor.h"
#include "ScreenEffectMng.h"
#include "ImageManager.h"

Actor::Actor()
{
	exRate_ = 1.0f;
	rotRate_ = 0.0f;

	animationCount_ = 0.0f;
	count_ = 0.0f;
	isTurnLeft_ = false;
	isMove_ = false;
	speed_ = { 0,0 };
	zSpeed_ = 0;
	jumpSpeed_ = 0;
	jumpFirstSpeed_ = -13.0f;
	jumpForce_ = 0.0f;
	isJump_ = false;
	isAnimEnd_ = false;
	isAttack_ = false;
	// まず待機状態に初期化
	//currentAnimation_ = "idle";

	gravity_ = new Gravity();

}

Actor::~Actor()
{
}

void Actor::ReadyToShot(void)
{
	isShot_ = true;
}

bool Actor::OnFloor(void)
{
	if (pos_.y >= 500)
	{
		return true;
	}
	return false;
}

bool Actor::Initialize(void)
{
	// ImageLoaderｸﾗｽの使用
	auto& imageMng = ImageManager::GetInstance();
	auto imageResource = imageMng.GetResource(type_);

	// ｱﾆﾒｰｼｮﾝﾌﾚｰﾑ、ｱﾆﾒｰｼｮﾝ名の吊り上げ
	auto animSet = imageMng.GetActionSet(type_);

	// ﾀｲﾌﾟ別に個々のｱﾆﾒｰｼｮﾝ名とｱﾆﾒｰｼｮﾝﾌﾚｰﾑの格納
	// もしかしたらこれはいらない...??
	for (auto anim = animSet.begin(); anim != animSet.end(); anim++)
	{
		animationSet_.try_emplace(anim->first, anim->second.first.second - anim->second.first.first);
		isLoop_.try_emplace(anim->first, anim->second.second);
	}

	alpha_percent = 100.0f;
	isDamaged_ = false;
	// 矩形情報の初期化
	RectInitializer();

	return true;
}

void Actor::RectInitializer(void)
{
	auto& imageMng = ImageManager::GetInstance();
	for (auto animSet = imageMng.GetActionSet(type_).begin();
		animSet != imageMng.GetActionSet(type_).end(); animSet++)
	{
		rect_.try_emplace(animSet->first);
		rect_[animSet->first].resize((animSet->second.first.second - animSet->second.first.first) + 1);
	}

	auto name = imageMng.GetActorName(type_);
	auto& collisionMng = CollisionManager::GetInstance();

	collisionMng.Load(rect_, name);
}

void Actor::Draw(void)
{
	auto& imageMng = ImageManager::GetInstance();

	drawPos_ = Vector2I(pos_.x, pos_.y + (z_ / 2));

	lpS_Effect.DrawRotaGraph_AlphaEffect(Vector2F(drawPos_.x, drawPos_.y),
		exRate_, rotRate_,
		imageMng.GetID(type_, currentAnimation_)[animationCount_],
		true, alpha_percent, isTurnLeft_);

	// 今のｱﾆﾒｰｼｮﾝでの矩形を検索して格納
	auto it = rect_.find(currentAnimation_);
	// 今のｱﾆﾒｰｼｮﾝの現在のﾌﾚｰﾑの中の矩形数を全検索して描画
	for (auto collider : it->second[animationCount_])
	{
		collider->Draw(drawPos_);
	}
}

void Actor::UpDateAnimation(const std::string& animName)
{
	animationCount_ += 0.1f;
	if (animationSet_.find(animName) != animationSet_.end())
	{
		if ((int)animationCount_ >= animationSet_.find(animName)->second)
		{
			if (isLoop_[animName])
			{
				animationCount_ = 0.0f;
			}
			else
			{
				animationCount_ = animationSet_.find(animName)->second;
				isAttack_ = false;
				isAnimEnd_ = true;
			}
		}
	}
}

void Actor::ChangeAnimation(std::string animName)
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

const std::string& Actor::GetCurrentAnimation(void)
{
	return currentAnimation_;
}
