#include <DxLib.h>
#include "Pod.h"
#include "ControlledPlayer.h"
#include "WeaponBase.h"
#include "EnemyAIManager.h"
#include "PodAI.h"
#include "AICollider.h"
#include "EnemyBullet.h"
#include "ImageManager.h"

// Zç¿ïWÇçáÇÌÇπÇÈçsìÆÇ…à⁄ÇÈãóó£
constexpr int arrangementZDistance = 150;

Pod::Pod(Vector2I pos,
	int z, 
	ActorType type,
	std::vector<std::shared_ptr<ControlledPlayer>>& player):
	Enemy(player)
{
	pos_ = pos;
	size_ = Vector2I(55,55);
	z_ = z;
	type_ = type;
	hpNum_ = 1;
	aiCollider_ = std::make_unique<AICollider>();
	aiSystem_ = std::make_shared<PodAI>(*this);
	damageRate_ = 20.0f;
	attackRate_ = 2.0f;
	maxHp_ = 100;

	name_ = "Pod";

	lpImage.LoadDiv("podmuzzleFlash", Vector2I(55, 60), Vector2I(5, 1));
	Initialize();
	Actor::Initialize();
	ChangeAnimation("walk");

}

Pod::~Pod()
{
}

void Pod::UpDate(void)
{
	gravity_->Apply(pos_);
	aiCollider_->SetPos(pos_,z_);

	// ±∆“∞ºÆ›
	UpDateAnimation(currentAnimation_);
}

void Pod::Draw_(void)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 80);
	DrawOvalAA(pos_.x, pos_.y + (z_ / 2) + (size_.y / 2), size_.x / 2.8f, size_.y / 4, 10.0f, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	Actor::Draw();
	Enemy::Draw();
	if (isTurnLeft_)
	{
		muzzleFlashPos_ = Vector2I(pos_.x -40, pos_.y - 5 + (z_/2));
	}
	else
	{
		muzzleFlashPos_ = Vector2I(pos_.x +40, pos_.y - 5 + (z_ / 2));
	}
	if (currentAnimation_ == "attack_release")
	{
		DrawRotaGraph(muzzleFlashPos_.x, muzzleFlashPos_.y,
			1.0f, 0.0f, lpImage.GetDivID("podmuzzleFlash")[muzzleFlashAnimationCount_],
			true,isTurnLeft_,false);
	}
}
