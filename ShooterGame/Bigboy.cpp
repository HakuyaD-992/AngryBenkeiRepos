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
	aiCollider_ = std::make_unique<AICollider>();
	aiSystem_ = std::make_shared<BigboyAI>(*this);

	hp_ = 100;
	damageRate_ = 1.0f;
	attackRate_ = 10.0f;
	name_ = "Bigboy";
	Initialize();
	Actor::Initialize();
	ChangeAnimation("idle");
	id_ = enemyNo_;
	enemyNo_++;
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
	Actor::Draw();
	DrawFormatString(100, 100, 0xffffff, "z_:%d", z_);
}
