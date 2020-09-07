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
	if (me_.CheckHitPlayerBullet(me_.GetNearestPlayer()->GetCurrentWeapon()->GetBullets()))
	{
		me_.ChangeAnimation("hit");
		updater_ = &PodAI::OnDamaged;
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
	// �����ŋ����̌v�Z������āA�ϐ��ɓ���Ă���
	auto distance = me_.GetNearestPlayer()->GetPos().x - me_.GetPos().x;

	// Pod�ƃv���C���[�Ƃ̋�������苗���ɂȂ��
	// Pod�̓v���C���[��Z���ɍ��킹��s��������
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
		if (!createBulletFlag_)
		{
			createBulletFlag_ = true;
		}
		if (me_.GetisAnimEnd())
		{
			me_.GetisHitAICollider() = false;
			me_.ChangeAnimation("walk");
			me_.GetAIState() = AIState::Walk;
			updater_ = &PodAI::Walk;
			createBulletFlag_ = false;
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
		me_.ChangeAnimation("walk");
		updater_ = &PodAI::Walk;
		return true;
	}
	return false;
}

bool PodAI::Evacuate(std::list<std::shared_ptr<Enemy>>& enemies)
{
	return true;
}

bool PodAI::Run(std::list<std::shared_ptr<Enemy>>& enemies)
{
	// ��ڲ԰�̌���
	auto playerIsTurnLeft = me_.GetNearestPlayer()->GetisTurnFlag();
	// ������ڲ԰���E�������Ă������ڲ԰�̍����ɍs���܂Œ��i
	if (!playerIsTurnLeft)
	{
		me_.GetSpeed().x = -2;
	}
	// ������ڲ԰�����������Ă������ڲ԰�̉E���ɍs���܂Œ��i
	else
	{
		me_.GetSpeed().x = 2;
	}

	// ���i������
	me_.GetPos().x += me_.GetSpeed().x;

	// ��ڲ԰���߼޼��
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

void PodAI::Initialize(void)
{
	updater_ = &PodAI::Walk;
}