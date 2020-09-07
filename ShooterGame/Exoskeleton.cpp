#include <DxLib.h>
#include "Exoskeleton.h"
#include "ScreenEffectMng.h"
#include "ImageManager.h"
#include "ControlledPlayer.h"
#include "WeaponBase.h"
#include "EnemyAIManager.h"
#include "ExoskeletonAI.h"
#include "AICollider.h"
#include "EnemyBullet.h"

Exoskeleton::Exoskeleton(Vector2I pos,
	int z,ActorType type,
	std::vector<std::shared_ptr<ControlledPlayer>>& player) :
	Enemy(player)
{
	pos_ = pos;
	z_ = z;
	type_ = type;
	aiCollider_ = std::make_unique<AICollider>();
	aiSystem_ = std::make_shared<ExoskeletonAI>(*this);


	size_ = Vector2I(48, 48);
	id_ = enemyNo_;
	hp_ = 20;
	Initialize();
	Actor::Initialize();
	ChangeAnimation("run");
	updater = &Exoskeleton::Run;
	enemyNo_++;
	frame = 0;
}

Exoskeleton::~Exoskeleton()
{
}

void Exoskeleton::UpDate(void)
{
	frame++;

	if (frame % 10 == 1)
	{
		afterimage_limit.emplace_back(make_pair(Vector2F(pos_.x, pos_.y + (z_ / 2)), 10));
	}

	afterimage_limit.front().second--;
	if (afterimage_limit.front().second <= 0)
	{
		afterimage_limit.erase(afterimage_limit.begin());
	}

	gravity_->Apply(pos_);
	aiCollider_->SetPos(pos_, z_);

	if (CheckHitPlayerBullet(nearestPlayer_->GetCurrentWeapon()->GetBullets()))
	{
		Delete();
	}

	UpDateAnimation(currentAnimation_);
}

void Exoskeleton::Draw_(void)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	for (auto pos : afterimage_limit)
	{
		lpS_Effect.DrawRotaGraph(pos.first, 1, 0,lpImage.GetID(type_, "run")[animationCount_], true);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);
	Actor::Draw();
}

void Exoskeleton::Run(void)
{
	ChangeAnimation("run");
}

void Exoskeleton::ArrangementZ(void)
{

}

void Exoskeleton::Attack(void)
{
}

void Exoskeleton::Evacuation(void)
{
}

void Exoskeleton::RefillBullet(void)
{
}
