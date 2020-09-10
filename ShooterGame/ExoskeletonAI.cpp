#include <cmath>
#include "Collision.h"
#include "Enemy.h"
#include "Floor.h"
#include "ControlledPlayer.h"
#include "WeaponBase.h"
#include "ExoskeletonAI.h"

ExoskeletonAI::ExoskeletonAI(Enemy& enemy):
	AIBase(enemy)
{
	Initialize();
}

ExoskeletonAI::~ExoskeletonAI()
{
}

void ExoskeletonAI::Update(std::list<std::shared_ptr<Enemy>>& enemies)
{
	frame++;
	if (BoxOutCollision()(Vector2I(me_.GetPos().x,me_.GetZPos()),Vector2I(0,-320),Vector2I(floorX,floorZ)))
	{
		me_.ChangeAnimation("death");
		updater_ = &ExoskeletonAI::Death;
	}

	if (CircleCollision()(me_.GetType(),
		me_.SearchNearestPlayer()->GetPos() - me_.GetPos(),
		me_.GetSize() + me_.GetNearestPlayer()->GetSize(),
		me_.GetZPos() - me_.GetNearestPlayer()->GetZPos()))
	{
		me_.ChangeAnimation("death");
		me_.GetNearestPlayer()->GetOnDamaged() = true;
		updater_ = &ExoskeletonAI::Death;
	}

	for (auto enemy : enemies)
	{
		if (me_.GetId() != enemy->GetId())
		{
			if (CircleCollision()(enemy->GetType(),
				enemy->GetPos() - me_.GetPos(), enemy->GetSize() + me_.GetSize(),
				enemy->GetZPos() - me_.GetZPos()))
			{
				enemy->GetFriendlyFireFlag() = true;
				me_.ChangeAnimation("death");
				updater_ = &ExoskeletonAI::Death;
			}
		}
	}

	if (rad >= 0)
	{
		me_.GetisTurnFlag() = false;
	}
	else
	{
		me_.GetisTurnFlag() = true;
	}
	(this->*updater_)(enemies);
}

bool ExoskeletonAI::Run(std::list<std::shared_ptr<Enemy>>& enemies)
{
	if (me_.OnFloor() == true)
	{
		if ((frame / 2) % 60 == 59)
		{
			player_pos = Vector2I(me_.GetNearestPlayer()->GetPos().x, me_.GetNearestPlayer()->GetZPos());
			rad = atan2(player_pos.y - me_.GetZPos(), player_pos.x - me_.GetPos().x);
		}
		me_.GetPos().x += 5 * cos(rad);
		me_.GetZPos() += 5 * sin(rad);
	}
	else
	{
		player_pos = Vector2I(me_.GetNearestPlayer()->GetPos().x, me_.GetNearestPlayer()->GetZPos());
			rad = atan2(player_pos.y - me_.GetZPos(), player_pos.x - me_.GetPos().x);
	}

	return false;
}

bool ExoskeletonAI::Death(std::list<std::shared_ptr<Enemy>>& enemies)
{
	if (me_.GetisAnimEnd())
	{
		me_.Delete();
		return true;
	}
	return false;
}

void ExoskeletonAI::Initialize(void)
{
	frame = 0;
	updater_ = &ExoskeletonAI::Run;
}
