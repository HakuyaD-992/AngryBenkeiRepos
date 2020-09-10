#include <DxLib.h>
#include "ScreenEffectMng.h"
#include "ImageManager.h"
#include "ControlledPlayer.h"
#include "WeaponBase.h"
#include "EnemyAIManager.h"
#include "AICollider.h"
#include "EnemyBullet.h"
#include "SpacenautAI.h"
#include "Spacenaut.h"

Spacenaut::Spacenaut(Vector2I pos, int z, ActorType type, std::vector<std::shared_ptr<ControlledPlayer>>& player) :
	Enemy(player)
{
	pos_ = pos;
	z_ = z;
	type_ = type;
	aiCollider_ = std::make_unique<AICollider>();
	aiSystem_ = std::make_shared<SpacenautAI>(*this);

	size_ = Vector2I(68, 68);
	id_ = enemyNo_;
	hp_ = 20;
	name_ = "Spacenaut";
	Initialize();
	Actor::Initialize();
	ChangeAnimation("walk");
	enemyNo_++;
}

Spacenaut::~Spacenaut()
{
}

void Spacenaut::UpDate(void)
{
	gravity_->Apply(pos_);
	aiCollider_->SetPos(pos_, z_);

	// ±ÆÒ°¼®Ý
	UpDateAnimation(currentAnimation_);
}

void Spacenaut::Draw_(void)
{
	Actor::Draw();
}