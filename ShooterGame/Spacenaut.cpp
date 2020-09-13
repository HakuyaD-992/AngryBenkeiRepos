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
	hpNum_ = 2;
	aiCollider_ = std::make_unique<AICollider>();
	aiSystem_ = std::make_shared<SpacenautAI>(*this);

	size_ = Vector2I(68, 68);
	maxHp_ = 100;
	name_ = "Spacenaut";
	Initialize();
	Actor::Initialize();
	ChangeAnimation("walk");

}

Spacenaut::~Spacenaut()
{
}

void Spacenaut::UpDate(void)
{
	gravity_->Apply(pos_);
	aiCollider_->SetPos(pos_, z_);

	// ��Ұ���
	UpDateAnimation(currentAnimation_);
}

void Spacenaut::Draw_(void)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 80);
	DrawOvalAA(pos_.x, pos_.y + (z_ / 2) + (size_.y / 2), size_.x / 2.8f, size_.y / 4, 10.0f, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	Actor::Draw();
	Enemy::Draw();
}