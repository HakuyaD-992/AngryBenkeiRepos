#include <DxLib.h>

#include "Bigboy.h"
#include "BigboyAI.h"
#include "AICollider.h"
#include "ImageManager.h"

Bigboy::Bigboy(Vector2I pos, int z, ActorType type, 
	std::vector<std::shared_ptr<ControlledPlayer>>& player):
	Enemy(player)
{
	pos_ = pos;
	size_ = Vector2I(300, 300);
	z_ = z;
	type_ = type;
	hpNum_ = 3;
	maxHp_ = 100;
	aiCollider_ = std::make_unique<AICollider>();
	aiSystem_ = std::make_shared<BigboyAI>(*this);

	damageRate_ = 1.0f;
	attackRate_ = 10.0f;
	name_ = "Bigboy";
	Initialize();
	Actor::Initialize();
	ChangeAnimation("idle");
}

Bigboy::~Bigboy()
{
}

void Bigboy::UpDate(void)
{
	if (!isJump_)
	{
		gravity_->Apply(pos_);
	}
	aiCollider_->SetPos(pos_, z_);

	// ±ÆÒ°¼®Ý
	UpDateAnimation(currentAnimation_);
}

void Bigboy::Draw_(void)
{
	auto shadow = 100 + (pos_.y - 500);
	if (shadow >= 255)
	{
		shadow = 255;
	}
	if (shadow <= 0)
	{
		shadow = 0;
	}
	if (currentAnimation_ != "death")
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, shadow);
		DrawOvalAA(pos_.x, pos_.y + (z_ / 2) + 100, shadowRadius_.x / 1.5f, shadowRadius_.y / 3, 10.0f, 0x000000, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	Actor::Draw();
	Enemy::Draw();
}
