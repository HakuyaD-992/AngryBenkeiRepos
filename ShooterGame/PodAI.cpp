#include "PodAI.h"
#include "Enemy.h"
#include "ControlledPlayer.h"
#include "WeaponBase.h"

PodAI::PodAI(Enemy& enemy):
	AIBase(enemy)
{
	Initialize();
}

PodAI::~PodAI()
{
}

void PodAI::Update(std::list<std::shared_ptr<Enemy>>& enemies)
{
	if (me_.GetOnDamaged())
	{
		me_.ChangeAnimation("hit");
		updater_ = &PodAI::OnDamaged;
	}

	if (me_.GetFriendlyFireFlag())
	{
		me_.ChangeAnimation("death");
		updater_ = &PodAI::Death;
	}
	
	(this->*updater_)(enemies);
}

bool PodAI::Walk(std::list<std::shared_ptr<Enemy>>& enemies)
{
	if (me_.GetPos().x > me_.GetNearestPlayer()->GetPos().x)
	{
		me_.GetisTurnFlag() = true;
		me_.GetSpeed().x = -2;
	}
	if (me_.GetPos().x < me_.GetNearestPlayer()->GetPos().x)
	{
		me_.GetisTurnFlag() = false;
		me_.GetSpeed().x = 2;
	}

	me_.GetPos().x += me_.GetSpeed().x;
	// ここで距離の計算をやって、変数に入れている
	auto distance = me_.GetNearestPlayer()->GetPos().x - me_.GetPos().x;

	// Podとプレイヤーとの距離が一定距離になれば
	// PodはプレイヤーのZ軸に合わせる行動をする
	if (abs(distance) < 150)
	{
		me_.GetAIState() = AIState::ZArrange;
		updater_ = &PodAI::Z_Arrangement;
		return true;
	}
	if (IsHitFriends(enemies))
	{
		me_.GetAIState() = AIState::Run;
		updater_ = &PodAI::Run;
		return true;
	}
}

bool PodAI::Z_Arrangement(std::list<std::shared_ptr<Enemy>>& enemies)
{
	if (me_.GetisTurnFlag())
	{
		me_.GetSpeed().x = -1;
	}
	else
	{
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

	me_.GetZPos() += me_.GetZSpeed();

	if (IsHitFriends(enemies))
	{
		me_.GetAIState() = AIState::Run;
		updater_ = &PodAI::Run;
		return true;
	}

	if (abs(me_.GetZPos() - playerZ) <= 3)
	{
		me_.ChangeAnimation("attack_prepare");
		me_.GetAIState() = AIState::Attack;
		updater_ = &PodAI::Attack;
		return true;
	}
}

bool PodAI::Attack(std::list<std::shared_ptr<Enemy>>& enemies)
{
	if (me_.GetisAnimEnd())
	{
		me_.ChangeAnimation("attack_release");
	}

	if (me_.GetCurrentAnimation() == "attack_release")
	{
		me_.AddMuzzleFlashAnimationCount(0.1f);
		if (me_.GetmuzzleFlashAnimationCount() >= 5.0f)
		{
			me_.GetisHitAICollider() = false;
			me_.GetmuzzleFlashAnimationCount() = 0.0f;
			me_.ChangeAnimation("walk");
			me_.GetAIState() = AIState::Walk;
			updater_ = &PodAI::Walk;
			return true;
		}
	}
	else
	{
		if (me_.GetPos().x > me_.GetNearestPlayer()->GetPos().x)
		{
			me_.GetisTurnFlag() = true;
			me_.GetSpeed().x = -2;
		}
		if (me_.GetPos().x < me_.GetNearestPlayer()->GetPos().x)
		{
			me_.GetisTurnFlag() = false;
			me_.GetSpeed().x = 2;
		}
	}
}

bool PodAI::OnDamaged(std::list<std::shared_ptr<Enemy>>& enemies)
{
	if (me_.GetisAnimEnd())
	{
		if (me_.GetHp() <= 0)
		{
			me_.GetHpNum()--;
			
			if (me_.GetHpNum() <= 0)
			{
				me_.ChangeAnimation("death");
				updater_ = &PodAI::Death;
			}
			else
			{
				me_.GetHp() = me_.GetMaxHp();
			}
			return true;
		}
		else
		{
			me_.ChangeAnimation("walk");
			updater_ = &PodAI::Walk;
			return true;
		}
	}
	me_.GetOnDamaged() = false;

	return false;
}

bool PodAI::Evacuate(std::list<std::shared_ptr<Enemy>>& enemies)
{
	return true;
}

bool PodAI::Run(std::list<std::shared_ptr<Enemy>>& enemies)
{
	// ﾌﾟﾚｲﾔｰの向き
	auto playerIsTurnLeft = me_.GetNearestPlayer()->GetisTurnFlag();
	// もしﾌﾟﾚｲﾔｰが右を向いていればﾌﾟﾚｲﾔｰの左側に行くまで直進
	if (!playerIsTurnLeft)
	{
		me_.GetSpeed().x = -2;
	}
	// もしﾌﾟﾚｲﾔｰが左を向いていればﾌﾟﾚｲﾔｰの右側に行くまで直進
	else
	{
		me_.GetSpeed().x = 2;
	}

	// 直進させる
	me_.GetPos().x += me_.GetSpeed().x;

	// ﾌﾟﾚｲﾔｰのﾎﾟｼﾞｼｮﾝ
	auto playerPos = me_.GetNearestPlayer()->GetPos();

	if (!playerIsTurnLeft)
	{
		if (me_.GetPos().x <= playerPos.x - 100)
		{
			me_.GetAIState() = AIState::Attack;
			me_.ChangeAnimation("attack_prepare");
			updater_ = &PodAI::Attack;
			return true;
		}
	}
	else
	{
		if (me_.GetPos().x >= playerPos.x + 100)
		{
			me_.GetAIState() = AIState::Attack;
			me_.ChangeAnimation("attack_prepare");
			updater_ = &PodAI::Attack;
			return true;
		}
	}

	return false;
}

bool PodAI::Death(std::list<std::shared_ptr<Enemy>>& enemies)
{
	if (me_.GetisAnimEnd())
	{
		me_.Delete();
		return true;
	}
	return false;
}

void PodAI::Initialize(void)
{
	updater_ = &PodAI::Walk;
}