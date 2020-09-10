#include "BigboyAI.h"
#include "Enemy.h"
#include "ControlledPlayer.h"
#include "Floor.h"

BigboyAI::BigboyAI(Enemy& enemy):
	AIBase(enemy)
{
	Initialize();
}

BigboyAI::~BigboyAI()
{
}

void BigboyAI::Update(std::list<std::shared_ptr<Enemy>>& enemies)
{
	jumpActionFrame_++;

	if (me_.GetOnDamaged())
	{
		me_.ChangeAnimation("hit");
		updater_ = &BigboyAI::OnDamaged;
	}

	if (me_.GetFriendlyFireFlag())
	{
		me_.ChangeAnimation("hit");
		updater_ = &BigboyAI::OnDamaged;
	}

	(this->*updater_)(enemies);
}

void BigboyAI::Initialize(void)
{
	updater_ = &BigboyAI::Observe;
	walkFrame_ = 0;
	jumpActionFrame_ = 0;
	jumpSp_ = 0;
	jumpFirstSp_ = -45.0f;
	jumpForce_ = 0.0f;

	tackleAccelSp_ = 0.0f;
	tackleSp_ = 0.0f;
	tackleFirstSp_ = 25.0f;
}

bool BigboyAI::Observe(std::list<std::shared_ptr<Enemy>>& enemies)
{
	auto playerZ = me_.SearchNearestPlayer()->GetZPos();
	auto playerPos = me_.GetNearestPlayer()->GetPos();

	auto zdiff = playerZ - me_.GetZPos();
	auto distance = playerPos - me_.GetPos();
	if (me_.GetPos().x > me_.GetNearestPlayer()->GetPos().x)
	{
		me_.GetSpeed().x = -7;
		me_.GetisTurnFlag() = false;
	}
	if (me_.GetPos().x < me_.GetNearestPlayer()->GetPos().x)
	{
		me_.GetSpeed().x = 7;
		me_.GetisTurnFlag() = true;
	}

	if (jumpActionFrame_ >= 1000)
	{
		me_.IsJumping() = true;
		updater_ = &BigboyAI::Jump;
		return true;
		/*updater_ = &BigboyAI::Tackle;
		return true;*/
	}
	else
	{
		me_.ChangeAnimation("walk");
		updater_ = &BigboyAI::ZArrange;
	}
	//else if(abs(zdiff) <= 5)
	//{
	//	if (abs(distance.x) >= 150)
	//	{
	//		me_.ChangeAnimation("attack");
	//		updater_ = &BigboyAI::Attack;
	//		return true;
	//	}
	//}
	//else
	//{
	//	me_.ChangeAnimation("walk");
	//	updater_ = &BigboyAI::Walk;
	//	return true;
	//}

	return true;

}

bool BigboyAI::Walk(std::list<std::shared_ptr<Enemy>>& enemies)
{
	walkFrame_++;

	if (me_.GetPos().x > me_.GetNearestPlayer()->GetPos().x)
	{
		me_.GetisTurnFlag() = false;
		me_.GetSpeed().x = -1;
	}
	if (me_.GetPos().x < me_.GetNearestPlayer()->GetPos().x)
	{
		me_.GetisTurnFlag() = true;
		me_.GetSpeed().x = 1;
	}

	auto playerZ = me_.GetNearestPlayer()->GetZPos();

	if (me_.GetZPos() >= playerZ)
	{
		me_.GetZSpeed() = -1;
	}
	else
	{
		me_.GetZSpeed() = 1;
	}

	if (walkFrame_ <= 100)
	{
		me_.GetPos().x += me_.GetSpeed().x;
		me_.GetZPos() += me_.GetZSpeed();
	}
	else
	{
		walkFrame_ = 0.0f;
		me_.ChangeAnimation("idle");
		updater_ = &BigboyAI::Observe;
	}

	return true;
}

bool BigboyAI::ZArrange(std::list<std::shared_ptr<Enemy>>& enemies)
{
	auto playerZ = me_.GetNearestPlayer()->GetZPos();

	if (me_.GetZPos() >= playerZ)
	{
		me_.GetZSpeed() = -1;
	}
	else
	{
		me_.GetZSpeed() = 1;
	}

	me_.GetZPos() += me_.GetZSpeed();

	auto zdiff = playerZ - me_.GetZPos();

	if (abs(zdiff) <= 5)
	{
		updater_ = &BigboyAI::Tackle;
	}

	return false;
}

bool BigboyAI::Attack(std::list<std::shared_ptr<Enemy>>& enemies)
{
	if (me_.GetPos().x > me_.GetNearestPlayer()->GetPos().x)
	{
		me_.GetisTurnFlag() = false;
		me_.GetSpeed().x = -1;
	}
	if (me_.GetPos().x < me_.GetNearestPlayer()->GetPos().x)
	{
		me_.GetisTurnFlag() = true;
		me_.GetSpeed().x = 1;
	}
	if (me_.GetisAnimEnd())
	{
		me_.ChangeAnimation("idle");
		updater_ = &BigboyAI::Observe;
	}
	return true;
}

bool BigboyAI::Jump(std::list<std::shared_ptr<Enemy>>& enemies)
{
	jumpForce_++;
	jumpSp_ = jumpFirstSp_ + jumpForce_;

	me_.GetPos().x += me_.GetSpeed().x;
	me_.GetPos().y += jumpSp_;

	if (me_.OnFloor())
	{
		jumpActionFrame_ = 0;
		jumpSp_ = 0;
		jumpFirstSp_ = -45.0f;
		jumpForce_ = 0.0f;
		me_.IsJumping() = false;
		me_.ChangeAnimation("idle");
		updater_ = &BigboyAI::Observe;
	}
	return false;
}

bool BigboyAI::OnDamaged(std::list<std::shared_ptr<Enemy>>& enemies)
{
	if (me_.GetisAnimEnd())
	{
		if (me_.GetHp() <= 0)
		{
			me_.ChangeAnimation("death");
			updater_ = &BigboyAI::Death;
			return true;
		}
		else
		{
			me_.ChangeAnimation("idle");
			updater_ = &BigboyAI::Observe;
			return true;
		}
	}
	me_.GetOnDamaged() = false;

	return false;
}

bool BigboyAI::Death(std::list<std::shared_ptr<Enemy>>& enemies)
{

	return false;
}

bool BigboyAI::Tackle(std::list<std::shared_ptr<Enemy>>& enemies)
{
	tackleAccelSp_ += 0.7f;
	tackleSp_ = tackleFirstSp_ - tackleAccelSp_;

	if (me_.GetisTurnFlag())
	{
		me_.GetPos().x += tackleSp_;
	}
	else
	{
		me_.GetPos().x -= tackleSp_;
	}

	if (tackleSp_ <= 0.0f)
	{
		tackleAccelSp_ = 0.0f;
		tackleSp_ = 0.0f;
		tackleFirstSp_ = 25.0f;
		updater_ = &BigboyAI::GoBack;
	}

	return false;
}

bool BigboyAI::GoBack(std::list<std::shared_ptr<Enemy>>& enemies)
{
	if (me_.GetisTurnFlag())
	{
		me_.GetSpeed().x = -1;
	}
	else
	{
		me_.GetSpeed().x = 1;
	}

	me_.GetPos().x += me_.GetSpeed().x;
	if (me_.GetisTurnFlag())
	{
		if (me_.GetPos().x <= 30)
		{
			me_.GetPos().x = 30;
			updater_ = &BigboyAI::Observe;
		}
	}
	else
	{
		if (me_.GetPos().x >= floorX - 100)
		{
			me_.GetPos().x = floorX - 100;
			updater_ = &BigboyAI::Observe;
		}
	}

	return false;
}
