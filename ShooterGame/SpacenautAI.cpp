#include "Enemy.h"
#include "ControlledPlayer.h"
#include "SpacenautAI.h"

SpacenautAI::SpacenautAI(Enemy& enemy):
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
		me_.GetAlpha() = (100 / (((damage_anim_frame/10) % 2) + 1));
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
	updater_ = &SpacenautAI::Walk;
	return true;
}

bool SpacenautAI::Walk(std::list<std::shared_ptr<Enemy>>& enemies)
{
	if (me_.GetPos().x < 800 - 48 && me_.GetPos().x > 48)
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

	if (me_.GetPos().x > me_.GetNearestPlayer()->GetPos().x)
	{
		me_.GetisTurnFlag() = true;
	}
	if (me_.GetPos().x < me_.GetNearestPlayer()->GetPos().x)
	{
		me_.GetisTurnFlag() = false;
	}
	me_.GetPos().x += me_.GetSpeed().x;
	return true;
}

bool SpacenautAI::ArrangementZ(std::list<std::shared_ptr<Enemy>>& enemies)
{
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
	anim_flag = false;
	updater_ = &SpacenautAI::Search;
}
