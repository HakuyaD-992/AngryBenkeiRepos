#include <DxLib.h>
#include "Actor.h"
#include "ImageManager.h"
#include "ScreenEffectMng.h"

Actor::Actor()
{
	exRate_ = 1.0f;
	rotRate_ = 0.0f;
	shadowRadius_ = { 0,0 };

	animationCount_ = 0.0f;
	count_ = 0.0f;
	isTurnLeft_ = false;
	isMove_ = false;
	speed_ = { 0,0 };
	zSpeed_ = 0;
	z_ = 0;
	type_ = ActorType::Max;
	jumpSpeed_ = 0;
	drawHpCnt_ = 0;
	jumpFirstSpeed_ = -13.0f;
	jumpForce_ = 0.0f;
	isJump_ = false;
	isAnimEnd_ = false;
	isAttack_ = false;
	onDamaged_ = false;
	isDrawHp_ = false;
	deleteFlag_ = false;
	duration_ = 0.0f;
	alpha_percent = 0.0f;
	// まず待機状態に初期化
	//currentAnimation_ = "idle";

	gravity_ = new Gravity();

}

Actor::~Actor()
{
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
	shadowRadius_ = { size_.x / 2, size_.y / 2 };

	// ｱﾆﾒｰｼｮﾝﾌﾚｰﾑ、ｱﾆﾒｰｼｮﾝ名の吊り上げ
	auto animSet = imageMng.GetActionSet(type_);

	alpha_percent = 100.0f;

	switch (type_)
	{
	case ActorType::Player:
		hpPos_ = Vector2I(125, 42);
		break;
	case ActorType::Pod:
	case ActorType::Exoskeleton:
	case ActorType::Spacenaut:
		hpPos_ = Vector2I(675, 42);
		break;
	case ActorType::Bigboy:
		hpPos_ = Vector2I(675, 63);
		break;
	case ActorType::Max:
		break;
	default:
		break;
	}
	lpImage.Load("UI/" + name_ + "_Hp");
	// ﾀｲﾌﾟ別に個々のｱﾆﾒｰｼｮﾝ名とｱﾆﾒｰｼｮﾝﾌﾚｰﾑの格納
	// もしかしたらこれはいらない...??
	for (auto anim = animSet.begin(); anim != animSet.end(); anim++)
	{
		animationSet_.try_emplace(anim->first, anim->second.first.second - anim->second.first.first);
		isLoop_.try_emplace(anim->first, anim->second.second);
	}

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

	if (type_ == ActorType::Player)
	{
		DrawGraph(10, 10,
			lpImage.GetID("UI/" + name_ + "_Hp"), true);
		DrawBox(76, 53, 76 + 160 * static_cast<float>(hp_[0]) / 100.0f, 65, 0x0000ff, true);
	}

	if (type_ != ActorType::Bigboy)
	{
		drawPos_ = Vector2I(pos_.x, pos_.y + (z_ / 2));
	}
	else
	{
		drawPos_ = Vector2I(pos_.x, pos_.y - 30 + (z_ / 2));
	}
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
	if (type_ != ActorType::Bigboy)
	{
		animationCount_ += 0.1f;
	}
	else
	{
		if (currentAnimation_ == "hit")
		{
			animationCount_ += 0.3f;
		}
		else
		{
			animationCount_ += 0.2f;
		}
	}
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
