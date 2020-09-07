#include "Exoskeleton.h"
#include "ControlledPlayer.h"
#include "WeaponBase.h"
#include "EnemyAIManager.h"
#include "PodAI.h"
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
	size_ = Vector2I(48, 48);
	id_ = enemyNo_;
	Initialize();
	Actor::Initialize();
	ChangeAnimation("run");
	updater = &Exoskeleton::Run;
	enemyNo_++;
}

Exoskeleton::~Exoskeleton()
{
}

void Exoskeleton::UpDate(void)
{
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
