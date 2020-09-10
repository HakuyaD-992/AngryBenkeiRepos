#include <DxLib.h>
#include "SoundManager.h"
#include "AIBase.h"
#include "Enemy.h"
#include "PodAI.h"
#include "AICollider.h"
#include "ControlledPlayer.h"

AIBase::AIBase(Enemy& enemy):
	me_(enemy)
{
	createBulletFlag_ = false;
}

AIBase::~AIBase()
{
}

void AIBase::AIAction(std::list<std::shared_ptr<Enemy>>& enemies)
{
	// Ž©•ª‚ªŒ»ÝÌßÚ²Ô°‚Ì”wŒã‚É‚¢‚é‚©Áª¯¸
	auto playerIsLeft = me_.SearchNearestPlayer()->GetisTurnFlag();
	auto playerPos = me_.SearchNearestPlayer()->GetPos();
	auto isBehind = false;
	if (playerIsLeft)
	{
		if (me_.GetPos().x > playerPos.x)
		{
			isBehind = true;
		}
	}
	else
	{
		if (me_.GetPos().x < playerPos.x)
		{
			isBehind = true;
		}
	}
	if (me_.GetOnDamaged())
	{
		if (me_.GetHp() <= 0)
		{
			lpSound.Play("explosion",DX_PLAYTYPE_BACK);
		}
	}
	// Ž©•ª‚ªÌßÚ²Ô°‚Ì”wŒã‚É‚¢‚é‚©‚¢‚È‚¢‚©Ì×¸Þ‚ð¾¯Ä
	me_.SetisBehindPlayer(isBehind);

	Update(enemies);
}

bool AIBase::IsHitFriends(std::list<std::shared_ptr<Enemy>>& enemies)
{
	auto isBehindPlayer = false;
	for (auto e1 : enemies)
	{
		isBehindPlayer = e1->GetisBehindPlayer();
	}
	auto myColPos = me_.GetAICollider()->GetPos();
	auto myColPosZ = me_.GetAICollider()->GetZPos();
	if (!isBehindPlayer)
	{
		for (auto e2 : enemies)
		{
			if (me_.GetId() != e2->GetId())
			{
				if (!e2->GetisHitAICollider() &&
					!me_.GetisHitAICollider())
				{
					auto otherColPos
						= Vector2I(e2->GetAICollider()->GetPos().x,
							e2->GetAICollider()->GetPos().y + (e2->GetAICollider()->GetZPos() / 2));
					if (abs(otherColPos.x - myColPos.x) <= (size / 2) &&
						abs(otherColPos.y - myColPos.y) <= (size / 2))
					{
						e2->GetisHitAICollider() = true;
						me_.GetisHitAICollider() = true;
						return true;
					}
					else
					{
						return false;
					}
				}
			}
		}
	}
	return false;
}
