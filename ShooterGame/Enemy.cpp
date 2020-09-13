#include <DxLib.h>

#include "Enemy.h"
#include "ImageManager.h"
#include "ControlledPlayer.h"
#include "EnemyAIManager.h"
#include "AICollider.h"
#include "EnemyBullet.h"
#include "Collision.h"
#include "WeaponBase.h"
#include "SoundManager.h"
#include "EffectManager.h"

std::array<int,4> Enemy::enemyNo_ = { 0,0,0,0 };

Enemy::Enemy(std::vector<std::shared_ptr<ControlledPlayer>>& player):
	player_(player)
{
	id_ = 0;
	hpNum_ = 0;
	maxHp_ = 0;
	AIstate_ = AIState::Walk;
	isHitAICollider_ = false;
	isBehindPlayer_ = false;
	deleteFlag_ = false;
	isShot_ = false;
	friendlyFireFlag_ = false;
	isShotPrepare_ = true;

	myLevel_ = Level::Lv_1;

	muzzleFlashAnimationCount_ = 0.0f;
	shotInterval_ = 0.0f;
}

Enemy::~Enemy()
{
}

void Enemy::Action(void)
{
	if (type_ == ActorType::Bigboy)
	{
		if (!isShotPrepare_)
		{
			shotInterval_++;
			if (shotInterval_ >= 100)
			{
				isShotPrepare_ = true;
				shotInterval_ = 0;
			}
		}
	}
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

	myLevel_ = (Level)(Level::Max - hpNum_);

	if (onDamaged_)
	{
		switch (nearestPlayer_->GetCurrentWeapon()->GetType())
		{
		case WeaponType::Pistol:
			hp_[hpNum_-1] -= 2 * damageRate_;
			break;

		case WeaponType::ShotGun:
			hp_[hpNum_-1] -= 5 * damageRate_;
			break;
		case WeaponType::SubMachineGun:
			hp_[hpNum_-1] -= 1 * damageRate_;
			break;

		default:
			break;
		}
	}

	UpDate();
}

void Enemy::Draw(void)
{
	Actor::Draw();

	if (type_ != ActorType::Bigboy)
	{
		if (onDamaged_)
		{
			isDrawHp_ = true;
		}
		if (isDrawHp_)
		{
			drawHpCnt_++;
		}

		if (drawHpCnt_ >= 1 && drawHpCnt_ <= 30)
		{
			HpDraw();
		}
		else
		{
			if (drawHpCnt_ > 100)
			{
				isDrawHp_ = false;
				drawHpCnt_ = 0;
			}
		}
		DrawFormatString(hpPos_.x - 200, hpPos_.y - 30, 0xffffff, (name_ + std::to_string(id_)).c_str());
	}
	else
	{
		HpDraw();
	}
}

bool Enemy::Initialize(void)
{
	auto& imageMng = ImageManager::GetInstance();
	auto imageResource = imageMng.GetResource(type_);

	id_ = enemyNo_[static_cast<int>(type_) - 1];
	enemyNo_[static_cast<int>(type_) - 1]++;

	hp_.resize(hpNum_);

	for (int i = 0; i < hpNum_; i++)
	{
		hp_[i] = 100;
	}


	// 各ﾀｲﾌﾟの画像ﾃﾞｰﾀのﾛｰﾄﾞ
	imageMng.Load(type_, "atlus", imageResource.divSize_, imageResource.divCount_);
	return true;
}

void Enemy::ReadyToShot(void)
{
	isShotPrepare_ = true;
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
		if (CircleCollision()(type_,bullet->GetPos() - pos_,
			size_,
			bullet->GetZPos() - z_
			))
		{
			// 弾を消す
			bullet->Delete();
			return true;
		}
	}
	return false;
}

bool Enemy::CheckHitMyBulletToPlayer(std::vector<std::shared_ptr<BulletBase>>& bullets)
{
	for (auto bullet : bullets)
	{
		if (CircleCollision()(nearestPlayer_->GetType(),
			nearestPlayer_->GetPos() - bullet->GetPos(), nearestPlayer_->GetSize() + bullet->GetSize(),
			nearestPlayer_->GetZPos() - bullet->GetZPos()))
		{
			if ((int)attackRate_ > 0 && (int)attackRate_ <= 100)
			{
				nearestPlayer_->GetHp() -= (int)attackRate_;
				nearestPlayer_->GetOnDamaged() = true;
				bullet->Delete();
			}
			return true;
		}
	}
	return false;
}

std::shared_ptr<ControlledPlayer> Enemy::SearchNearestPlayer(void)
{

	// プレイヤーが2人以上の時	
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
			// プレイヤーが1人の時
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
	if (isShotPrepare_)
	{
		bullets.emplace_back(std::make_unique<EnemyBullet>(pos_, z_, type_, isTurnLeft_,(*this)));

		isShotPrepare_ = false;
	}
}

void Enemy::SetisBehindPlayer(bool& flg)
{
	isBehindPlayer_ = flg;
}

void Enemy::ResetEnemyNo(void)
{
	enemyNo_ = { 0,0,0,0 };
}

void Enemy::HpDraw(void)
{
	DrawRotaGraph(hpPos_.x, hpPos_.y, 1.0f, 0.0f,
		lpImage.GetID("UI/" + name_ + "_Hp"), true, false);
	for (int i = 0; i < hpNum_; i++)
	{
		DrawBox(hpPos_.x + 49, hpPos_.y + 10 + (i * 20),
			(hpPos_.x - 107) + hp_[i], hpPos_.y + 25 + (i * 20), 0x0000ff, true);
	}
	DrawFormatString(hpPos_.x - 10, hpPos_.y - 30, 0xffffff, (name_ + std::to_string(id_)).c_str());
}
