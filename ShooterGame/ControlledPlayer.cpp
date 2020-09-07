#include "ControlledPlayer.h"
#include "ImageManager.h"
#include "Application.h"
#include "AK69.h"
#include "SubMachinegun.h"
#include "Pistol.h"
#include "KeyConfiguration.h"
#include "Input.h"
#include "BulletBase.h"
#include "Collision.h"

int ControlledPlayer::player_ = 0;

ControlledPlayer::ControlledPlayer(Vector2I pos, int z, const ActorType& type/*, std::list<std::shared_ptr<Enemy>>& enemyList*/)
{
	pos_ = pos;
	type_ = type;
	// 奥行
	z_ = z;
	weaponsArrangementAmount_ = {0,0};
	deleteFlag_ = false;
	hp_ = 300;

	playerNo_ = (PLAYER)player_;
	player_++;

	Initialize();
}

ControlledPlayer::~ControlledPlayer()
{
}

void ControlledPlayer::UpDate(void)
{
	auto& app = Application::Instance();
	auto input = app.GetInput(playerNo_)->GetPeriData();

	gravity_->Apply(pos_);

	// 弾の消去
	currentWeapon_->GetBullets().erase(std::remove_if(currentWeapon_->GetBullets().begin(),
		currentWeapon_->GetBullets().end(),
		[&](std::shared_ptr<BulletBase>& bullet) {
			return bullet->GetDeleteFlag();
		}), currentWeapon_->GetBullets().end());

	auto weaponMoveSmallAmount = animationCount_ - 3.0f;

	if (currentAnimation_ == "attack")
	{
		if (isAnimEnd_)
		{
			ChangeAnimation("idle");
		}
	}

	speed_ = { 0,0 };
	zSpeed_ = 0;

	for (auto weapon : weapons_)
	{
		for (auto bullet : weapon->GetBullets())
		{
			bullet->UpDate();
		}
	}

	for (auto inputData : input)
	{
		if (currentWeapon_->GetAnimation() == "non")
		{
			if (currentWeapon_->GetHavingBulletNum() > 0)
			{
				if (inputData.first == KeyConfiguration::Fire)
				{
					if (currentWeapon_->GetType() == WeaponType::ShotGun ||
						currentWeapon_->GetType() == WeaponType::Pistol)
					{
						if (inputData.second[static_cast<int>(TrgFlag::Now)] &&
							!inputData.second[static_cast<int>(TrgFlag::Old)])
						{
							currentWeapon_->SetAnimation("fire");
							currentWeapon_->AddBullet();
							currentWeapon_->GetHavingBulletNum()--;
						}
					}
					if (currentWeapon_->GetType() == WeaponType::SubMachineGun)
					{
						if (inputData.second[static_cast<int>(TrgFlag::Now)])
						{
							currentWeapon_->SetAnimation("fire");
							currentWeapon_->AddBullet();
							currentWeapon_->GetHavingBulletNum()--;
						}
					}
				}
			}

			if (inputData.first == KeyConfiguration::Reload)
			{
				if (inputData.second[static_cast<int>(TrgFlag::Now)] &&
					!inputData.second[static_cast<int>(TrgFlag::Old)])
				{
					currentWeapon_->SetAnimation("reload");
				}
			}
		}

		if (inputData.first == KeyConfiguration::Left)
		{
			if (inputData.second[static_cast<int>(TrgFlag::Now)])
			{
				isTurnLeft_ = true;
				speed_.x = -2;
			}
		}
		if (inputData.first == KeyConfiguration::Right)
		{
			if (inputData.second[static_cast<int>(TrgFlag::Now)])
			{
				isTurnLeft_ = false;
				speed_.x = 2;
			}
		}
		if (inputData.first == KeyConfiguration::Down)
		{
			if (inputData.second[static_cast<int>(TrgFlag::Now)])
			{
				zSpeed_ = 2;
			}
		}
		if (inputData.first == KeyConfiguration::Up)
		{
			if (inputData.second[static_cast<int>(TrgFlag::Now)])
			{
				zSpeed_ = -2;
			}
		}

		if (currentWeapon_->GetAnimation() == "non")
		{
			// 今現在装備中の武器の変更
			if (inputData.first == KeyConfiguration::ChangeWeapon)
			{
				if (inputData.second[static_cast<int>(TrgFlag::Now)] &&
					!inputData.second[static_cast<int>(TrgFlag::Old)])
				{
					currentWeaponNo_ = (currentWeaponNo_ < (int)WeaponType::SubMachineGun) ? ++currentWeaponNo_ : 0;
					currentWeapon_ = weapons_[currentWeaponNo_];
				}
			}
		}
	}

	if ((speed_.x == 0) && (zSpeed_ == 0))
	{
		ChangeAnimation("idle");
	}
	else
	{
		ChangeAnimation("run");
	}

	if (isTurnLeft_)
	{
		if (currentWeapon_->GetType() == WeaponType::Pistol)
		{
			weaponsArrangementAmount_.x = -5;
		}
		if (currentWeapon_->GetType() == WeaponType::SubMachineGun)
		{
			weaponsArrangementAmount_.x = -10;
		}
		if (currentWeapon_->GetType() == WeaponType::ShotGun)
		{
			weaponsArrangementAmount_.x = -20;
		}
	}
	else
	{
		if (currentWeapon_->GetType() == WeaponType::Pistol)
		{
			weaponsArrangementAmount_.x = 5;
		}
		if (currentWeapon_->GetType() == WeaponType::SubMachineGun)
		{
			weaponsArrangementAmount_.x = 10;
		}
		if (currentWeapon_->GetType() == WeaponType::ShotGun)
		{
			weaponsArrangementAmount_.x = 20;
		}
	}

	switch (currentWeapon_->GetType())
	{
	case WeaponType::Pistol:
		weaponsArrangementAmount_.y = 17;

		break;
	case WeaponType::ShotGun:
		weaponsArrangementAmount_.y = 17;
		break;

	case WeaponType::SubMachineGun:
		weaponsArrangementAmount_.y = 17;
		break;
	default:
		break;
	}

	currentWeapon_->SetPos(Vector2I(pos_.x + weaponsArrangementAmount_.x,
		pos_.y + weaponsArrangementAmount_.y - abs(weaponMoveSmallAmount)), z_);

	Walk(speed_, zSpeed_);

	// 着地時
	if (OnFloor())
	{
		jumpFirstSpeed_ = -13.0f;
		jumpSpeed_ = 0;
		jumpForce_ = 0.0f;
		isJump_ = false;
	}

	UpDateAnimation(currentAnimation_);
}

void ControlledPlayer::Draw_(void)
{
	Actor::Draw();
	for (auto weapon : weapons_)
	{
		for (auto bullet : weapon->GetBullets())
		{
			bullet->Draw();
		}
	}
	DrawFormatString(100, 120, 0xffffff, "bulletNum:%d", currentWeapon_->GetHavingBulletNum());
}

bool ControlledPlayer::Initialize(void)
{
	auto& imageMng = ImageManager::GetInstance();
	auto imageResource = imageMng.GetResource(type_);
	currentWeaponNo_ = 0;
	// 各ﾀｲﾌﾟの画像ﾃﾞｰﾀのﾛｰﾄﾞ
	imageMng.Load(type_, "atlus", imageResource.divSize_, imageResource.divCount_);
	//weapons_.emplace_back(std::make_shared<Gun>(pos_, z_, WeaponType::Pistol));


	weapons_.emplace_back(std::make_shared<Pistol>(pos_, z_, WeaponType::Pistol));
	weapons_.emplace_back(std::make_shared<AK69>(pos_, z_, WeaponType::ShotGun));
	weapons_.emplace_back(std::make_shared<SubMachinegun>(pos_, z_, WeaponType::SubMachineGun));
	currentWeapon_ = weapons_[currentWeaponNo_];
	Actor::Initialize();
	return true;
}

void ControlledPlayer::Walk(const Vector2I& speed, const int& zSp)
{
	pos_.x += speed.x;
	z_ += zSp;
}

void ControlledPlayer::Jump(void)
{
	jumpForce_ += 0.5f;
	jumpSpeed_ = jumpFirstSpeed_ + jumpForce_;

	pos_.y += jumpSpeed_;
	if (jumpSpeed_ >= -7)
	{
		ChangeAnimation("jump");
	}
	if (jumpSpeed_ > 0)
	{
		ChangeAnimation("fall");
	}
}

void ControlledPlayer::Fire(void)
{
}
