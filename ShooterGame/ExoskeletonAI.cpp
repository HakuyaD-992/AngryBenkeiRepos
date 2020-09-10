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
