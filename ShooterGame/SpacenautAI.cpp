#include "Enemy.h"
#include "ControlledPlayer.h"
#include "SpacenautAI.h"
#include "Floor.h"

SpacenautAI::SpacenautAI(Enemy& enemy) :
	AIBase(enemy)
{
	Initialize();
}
SpacenautAI::~SpacenautAI()
{
}

void SpacenautAI::Update(std::list<std::shared_ptr<Enemy>>& enemies)
{
	if (me_.GetOnDamaged())
	{
		anim_flag = true;
		updater_ = &SpacenautAI::OnDamaged;
	}
	if (anim_flag)
	{
		damage_anim_frame++;
		me_.GetAlpha() = (100 / (((damage_anim_frame / 10) % 2) + 1));
	}
	if (damage_anim_frame >= 60)
	{
		anim_flag = false;
		damage_anim_frame = 0;
		me_.GetAlpha() = 100.0f;
	}
	(this->*updater_)(enemies);
}

bool SpacenautAI::Search(std::list<std::shared_ptr<Enemy>>& enemies)
{
	target_pos_z = me_.GetNearestPlayer()->GetZPos();
	for (auto enemy : enemies)
	{
		if (enemy->GetType() == ActorType::Bigboy)
		{
			partnerPos_ = enemy->GetPos();
		}
	}
	updater_ = &SpacenautAI::Walk;
	return true;
}

bool SpacenautAI::Walk(std::list<std::shared_ptr<Enemy>>& enemies)
{
	auto distance = partnerPos_.x - me_.GetPos().x;

	if (abs(distance) <= 30)
	{
		if (distance < 0)
		{
			moveRight_ = true;
		}
		else
		{
			moveLeft_ = true;
		}
	}
	else
	{
		if (me_.GetPos().x < 800 - 68 && me_.GetPos().x > 68)
		{
			if (me_.GetPos().x >= 400)
			{
				me_.GetSpeed().x = 1;
			}
			else
			{
				me_.GetSpeed().x = -1;
			}
		}
		else
		{
			me_.GetSpeed().x = 0;
			updater_ = &SpacenautAI::ArrangementZ;
		}
		me_.GetPos().x += me_.GetSpeed().x;

	}
	if (me_.GetPos().x > me_.GetNearestPlayer()->GetPos().x)
	{
		me_.GetisTurnFlag() = true;
	}
	if (me_.GetPos().x < me_.GetNearestPlayer()->GetPos().x)
	{
		me_.GetisTurnFlag() = false;
	}

	if (moveRight_)
	{
		me_.GetSpeed().x = 1;
	}
	if (moveLeft_)
	{
		me_.GetSpeed().x = -1;
	}

	me_.GetPos().x += me_.GetSpeed().x;

	if (moveRight_)
	{
		if (me_.GetPos().x >= floorX - 40)
		{
			me_.GetPos().x = floorX - 40;
			moveRight_ = false;
			updater_ = &SpacenautAI::ArrangementZ;
		}
	}

	if (moveLeft_)
	{
		if (me_.GetPos().x <= 50)
		{
			me_.GetPos().x = 50;
			moveLeft_ = false;
			updater_ = &SpacenautAI::ArrangementZ;
		}
	}


	//else
	//{
	//	updater_ = &SpacenautAI::ArrangementZ;
	//}
	
	return true;
}

bool SpacenautAI::ArrangementZ(std::list<std::shared_ptr<Enemy>>& enemies)
{
	target_pos_z = me_.GetNearestPlayer()->GetZPos();

	if (me_.GetZPos() >= target_pos_z)
	{
		me_.GetZSpeed() = -1;
	}
	else
	{
		me_.GetZSpeed() = 1;
	}

	me_.GetZPos() += me_.GetZSpeed();

	if (abs(me_.GetZPos() - target_pos_z) <= 3 && me_.OnFloor() == true)
	{
		updater_ = &SpacenautAI::Attack;
	}
	return true;
}

bool SpacenautAI::Attack(std::list<std::shared_ptr<Enemy>>& enemies)
{
	frame++;
	if (frame <= 60)
	{
		me_.ChangeAnimation("attack");
	}
	else
	{
		frame = 0;
		me_.ChangeAnimation("walk");
		updater_ = &SpacenautAI::Search;
	}
	return true;
}

bool SpacenautAI::OnDamaged(std::list<std::shared_ptr<Enemy>>& enemies)
{
	if (me_.GetHp() <= 0)
	{
		me_.ChangeAnimation("death");
		updater_ = &SpacenautAI::Death;
	}
	else
	{
		me_.ChangeAnimation("walk");
		updater_ = &SpacenautAI::Search;
	}
	me_.GetOnDamaged() = false;
	return false;
}

bool SpacenautAI::Death(std::list<std::shared_ptr<Enemy>>& enemies)
{
	if (me_.GetisAnimEnd())
	{
		me_.Delete();
		return true;
	}
	return false;
}

void SpacenautAI::Initialize(void)
{
	frame = 0;
	damage_anim_frame = 0;
	partnerPos_ = { 0,0 };
	moveLeft_ = false;
	moveRight_ = false;
	anim_flag = false;
	updater_ = &SpacenautAI::Search;
}
