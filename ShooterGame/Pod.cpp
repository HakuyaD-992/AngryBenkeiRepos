#include "Pod.h"
#include "ControlledPlayer.h"

Pod::Pod(Vector2I pos,
	int z, 
	ActorType type,
	std::list<std::shared_ptr<ControlledPlayer>>& player):
	Enemy(player)
{
	pos_ = pos;
	size_ = Vector2I(55,55);
	z_ = z;
	type_ = type;

	Initialize();
	Actor::Initialize();
	ChangeAnimation("walk");

	updater_ = &Pod::Walk;
}

Pod::~Pod()
{
}

void Pod::UpDate(void)
{
	gravity_->Apply(pos_);
	// s“®
	(this->*updater_)();
	// ±ÆÒ°¼®Ý
	UpDateAnimation(currentAnimation_);
}

void Pod::Draw_(void)
{
	Actor::Draw();
}

void Pod::Walk(void)
{
	for (auto player : player_)
	{
		if (pos_.x > player->GetPos().x)
		{
			isTurnLeft_ = true;
			speed_.x = -1;
		}
		if (pos_.x < player->GetPos().x)
		{
			isTurnLeft_ = false;
			speed_.x = 1;
		}
	}

	pos_.x += speed_.x;

	ChangeAnimation("walk");
}

void Pod::Z_Arrangement(void)
{
}

void Pod::Attack(void)
{
}

void Pod::Evacuate(void)
{
}
