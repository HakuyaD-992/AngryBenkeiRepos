#include "Exoskeleton.h"

Exoskeleton::Exoskeleton(Vector2I pos,
	int z,ActorType type,
	std::list<std::shared_ptr<ControlledPlayer>>& player):
	Enemy(player)
{
	pos_ = pos;
	z_ = z;
	type_ = type;
	size_ = Vector2I(48, 48);
	Initialize();
	Actor::Initialize();
	ChangeAnimation("run");
	updater = &Exoskeleton::Run;
}

Exoskeleton::~Exoskeleton()
{
}

void Exoskeleton::UpDate(void)
{
	gravity_->Apply(pos_);
	// “G‚Ìs“®‚Ì‘JˆÚ
	(this->*updater)();

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
