#include <DxLib.h>
#include "Actor.h"
#include "ImageManager.h"
#include "ScreenEffectMng.h"

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
	drawHpCnt_ = 0;
	jumpFirstSpeed_ = -13.0f;
	jumpForce_ = 0.0f;
	isJump_ = false;
	isAnimEnd_ = false;
	isAttack_ = false;
	onDamaged_ = false;
	isDrawHp_ = false;

	// ‚Ü‚¸‘Ò‹@ó‘Ô‚É‰Šú‰»
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
	// ImageLoader¸×½‚ÌŽg—p
	auto& imageMng = ImageManager::GetInstance();
	auto imageResource = imageMng.GetResource(type_);

	// ±ÆÒ°¼®ÝÌÚ°ÑA±ÆÒ°¼®Ý–¼‚Ì’Ý‚èã‚°
	auto animSet = imageMng.GetActionSet(type_);

	alpha_percent = 100.0f;

	if (type_ != ActorType::Player)
	{
		hpPos_ = Vector2I(650, 65);
	}
	else
	{
		hpPos_ = Vector2I(150, 85);
	}
	lpImage.LoadDiv("UI/hp", Vector2I(230, 64), Vector2I(1, 4));
	// À²Ìß•Ê‚ÉŒÂX‚Ì±ÆÒ°¼®Ý–¼‚Æ±ÆÒ°¼®ÝÌÚ°Ñ‚ÌŠi”[
	// ‚à‚µ‚©‚µ‚½‚ç‚±‚ê‚Í‚¢‚ç‚È‚¢...??
	for (auto anim = animSet.begin(); anim != animSet.end(); anim++)
	{
		animationSet_.try_emplace(anim->first, anim->second.first.second - anim->second.first.first);
		isLoop_.try_emplace(anim->first, anim->second.second);
	}

	// ‹éŒ`î•ñ‚Ì‰Šú‰»
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

	if (type_ != ActorType::Player)
	{
		if (onDamaged_)
		{
			isDrawHp_ = true;
		}
		if (isDrawHp_)
		{
			drawHpCnt_++;
		}

		if (drawHpCnt_ >= 1 && drawHpCnt_ <= 75)
		{
			DrawRotaGraph(hpPos_.x, hpPos_.y, 1.0f, 0.0f,
				lpImage.GetDivID("UI/hp")[static_cast<int>(type_)], true, false);
			DrawBox(hpPos_.x - 105, hpPos_.y + 10, (hpPos_.x - 105) + hp_, hpPos_.y + 25, 0x0000ff, true);
		}
		else
		{
			if (drawHpCnt_ > 100)
			{
				isDrawHp_ = false;
				drawHpCnt_ = 0;
			}
		}
	}
	else
	{
		DrawRotaGraph(hpPos_.x, hpPos_.y, 1.0f, 0.0f,
			lpImage.GetDivID("UI/hp")[static_cast<int>(type_)], true, false);
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

	// ¡‚Ì±ÆÒ°¼®Ý‚Å‚Ì‹éŒ`‚ðŒŸõ‚µ‚ÄŠi”[
	auto it = rect_.find(currentAnimation_);
	// ¡‚Ì±ÆÒ°¼®Ý‚ÌŒ»Ý‚ÌÌÚ°Ñ‚Ì’†‚Ì‹éŒ`”‚ð‘SŒŸõ‚µ‚Ä•`‰æ
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
