#include "Enemy.h"
#include "ImageManager.h"
#include "ControlledPlayer.h"
#include "EnemyAIManager.h"
#include "AICollider.h"
#include "EnemyBullet.h"
#include "Collision.h"
#include "WeaponBase.h"

int Enemy::enemyNo_ = 0;

Enemy::Enemy(std::vector<std::shared_ptr<ControlledPlayer>>& player):
	player_(player)
{
	id_ = 0;
	AIstate_ = AIState::Walk;
	isHitAICollider_ = false;
	isBehindPlayer_ = false;
	deleteFlag_ = false;
	onDamaged_ = false;
	isShot_ = true;

	muzzleFlashAnimationCount_ = 0.0f;
}

Enemy::~Enemy()
{
}

void Enemy::Action(void)
{
	if (OnFloor())
	{
		if (!onDamaged_)
		{
			if (currentAnimation_ != "death")
			{
				onDamaged_ = CheckHitPlayerBullet(nearestPlayer_->GetCurrentWeapon()->GetBullets());
			}
		}
	}
	if (onDamaged_)
	{
		switch (nearestPlayer_->GetCurrentWeapon()->GetType())
		{
		case WeaponType::Pistol:
			hp_ -= 2;
			break;

		case WeaponType::ShotGun:
			hp_ -= 5;
			break;
		case WeaponType::SubMachineGun:
			hp_--;
			break;

		default:
			break;
		}
	}
	UpDate();
}

bool Enemy::Initialize(void)
{
	auto& imageMng = ImageManager::GetInstance();
	auto imageResource = imageMng.GetResource(type_);

	// �e���߂̉摜�ް���۰��
	imageMng.Load(type_, "atlus", imageResource.divSize_, imageResource.divCount_);
	return true;
}

void Enemy::SetPos(const Vector2I& pos,int z)
{
	pos_ = pos;
	z_ = z;
}

bool Enemy::CheckHitPlayerBullet(const std::vector<std::shared_ptr<BulletBase>>& playerBullets)
{
	for (auto bullet : playerBullets)
	{
		if (CircleCollision()(bullet->GetPos() - pos_,
			size_,
			nearestPlayer_->GetZPos() - z_
			))
		{
			// �e������
			bullet->Delete();
			return true;
		}
	}
	return false;
}

std::shared_ptr<ControlledPlayer> Enemy::SearchNearestPlayer(void)
{
	// �v���C���[��2�l�ȏ�̎�	
	if (player_.size() >= 2)
	{
		auto distance1 = player_[0]->GetPos().x - pos_.x;
		auto distance2 = player_[1]->GetPos().x - pos_.x;

		if (distance1 < distance2)
		{
			nearestPlayer_ = player_[0];
		}
		else
		{
			if (distance1 > distance2)
			{
				nearestPlayer_ = player_[1];
			}
		}
	}
	else
	{
		if (player_.size() <= 1)
		{
			// �v���C���[��1�l�̎�
			nearestPlayer_ = player_[0];
		}
	}
	return nearestPlayer_;
}

std::shared_ptr<ControlledPlayer> Enemy::GetNearestPlayer(void)
{
	return nearestPlayer_;
}

const std::unique_ptr<AICollider>& Enemy::GetAICollider(void)
{
	return aiCollider_;
}

void Enemy::AddBullet(std::vector<std::shared_ptr<BulletBase>>& bullets)
{
	if (isShot_)
	{
		bullets.emplace_back(std::make_unique<EnemyBullet>(pos_, z_, type_, isTurnLeft_));
		isShot_ = false;
	}
}

void Enemy::ReadyToShot(void)
{
	isShot_ = true;
}

void Enemy::SetisBehindPlayer(bool& flg)
{
	isBehindPlayer_ = flg;
}
