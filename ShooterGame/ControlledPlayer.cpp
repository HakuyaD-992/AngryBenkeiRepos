#include <DxLib.h>

#include "ControlledPlayer.h"
#include "ImageManager.h"
#include "Application.h"
#include "Floor.h"
#include "AK69.h"
#include "SubMachinegun.h"
#include "Pistol.h"
#include "KeyConfiguration.h"
#include "Input.h"
#include "BulletBase.h"
#include "Collision.h"
#include "SoundManager.h"
#include "Item.h"
#include "MoneyItem.h"
#include "EffectManager.h"

int ControlledPlayer::player_ = 0;

ControlledPlayer::ControlledPlayer(Vector2I pos, int z, const ActorType& type,
	std::list<std::shared_ptr<Item>>& itemList/*,
	std::list<std::shared_ptr<MoneyItem>>& moneyList*/):
	items_(itemList)/*,moneyItems_(moneyList)*/
{
	pos_ = pos;
	type_ = type;
	// 奥行
	z_ = z;
	isHitEnemyZ_ = false;
	size_ = { 64,64 };
	weaponsArrangementAmount_ = {0,0};
	deleteFlag_ = false;

	isOnFloor_ = true;
	hpNum_ = 1;
	hp_.emplace_back(100);
	name_ = "Player";
	playerNo_ = (PLAYER)player_;
	player_++;

	use_Bullet = 0;
	havingMoney_ = { 0,0,0 };


	Initialize();
}

ControlledPlayer::~ControlledPlayer()
{
	player_ = 0;
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

	speed_ = { 0,0 };
	zSpeed_ = 0;

	for (auto weapon : weapons_)
	{
		for (auto bullet : weapon->GetBullets())
		{
			bullet->UpDate();
		}
	}

	// ﾌﾟﾚｲﾔｰのｱｲﾃﾑ取得
	GetItems();
	// ﾌﾟﾚｲﾔｰのお金取得
	//GetMoneys();

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
							lpSound.Play(currentWeapon_->GetWeaponName() + "/" + currentWeapon_->GetAnimation(),
								DX_PLAYTYPE_BACK);
							currentWeapon_->AddBullet();
							currentWeapon_->GetHavingBulletNum()--;
							use_Bullet++;
						}
					}
					if (currentWeapon_->GetType() == WeaponType::SubMachineGun)
					{
						if (inputData.second[static_cast<int>(TrgFlag::Now)])
						{
							currentWeapon_->SetAnimation("fire");
							currentWeapon_->AddBullet();
							currentWeapon_->GetHavingBulletNum()--;
							use_Bullet++;
						}
						if (inputData.second[static_cast<int>(TrgFlag::Now)] &&
							!inputData.second[static_cast<int>(TrgFlag::Old)])
						{
							lpSound.Play(currentWeapon_->GetWeaponName() + "/fire",
								DX_PLAYTYPE_LOOP);
						}
						if (!inputData.second[static_cast<int>(TrgFlag::Now)])
						{
							lpSound.Stop(currentWeapon_->GetWeaponName() + "/fire");
						}
					}
				}
			}
			else
			{
				lpSound.Stop(currentWeapon_->GetWeaponName() + "/fire");
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
					lpSound.Play(currentWeapon_->GetWeaponName() + "/get", DX_PLAYTYPE_BACK);
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
	// ﾀﾞﾒｰｼﾞを食らった処理
	if (onDamaged_)
	{
		alpha_percent -= 10;
		if (alpha_percent <= 0.0f)
		{
			lpSound.Play("damage", DX_PLAYTYPE_BACK);
			alpha_percent = 100.0f;
			onDamaged_ = false;
		}
	}

	// Hpが0になったら死ぬ
	if (hp_[hpNum_-1] <= 0)
	{
		Delete();
	}

	UpDateAnimation(currentAnimation_);
}

void ControlledPlayer::Draw_(void)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 80);
	DrawOvalAA(pos_.x, pos_.y + (z_ / 2) + (size_.y / 2), shadowRadius_.x / 2.8f, shadowRadius_.y / 4, 10.0f, 0x000000, true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	Actor::Draw();

	DrawFormatString(100, 100, 0xffffff, "%d", hp_[0]);
	for (auto weapon : weapons_)
	{
		for (auto bullet : weapon->GetBullets())
		{
			bullet->Draw();
		}
	}
	auto eraseFlag = false;

	for (auto& numPos : getBulletNumPos_)
	{
		numPos.first.first.y--;
		numPos.first.second -= 2;
		if (numPos.first.second <= 0)
		{
			numPos.first.second = 0;
			eraseFlag = true;
		}
	}
	if (eraseFlag)
	{
		getBulletNumPos_.pop_front();
	}

	DrawRotaGraph(weaponsUIPos_.x, weaponsUIPos_.y, 1.0f, 0.0f,
		lpImage.GetDivID("UI/weapons")[currentWeaponNo_], true, false);
	DrawRotaGraph(weaponsUIPos_.x + 130, weaponsUIPos_.y, 1.0f, 0.0f,
		lpImage.GetID("UI/bullets"), true, false);
	switch (currentWeapon_->GetType())
	{
	case WeaponType::Pistol:
		if (currentWeapon_->GetHavingBulletNum() <= 3)
		{
			addBlendFlag_ = true;
		}
		else
		{
			addBlendFlag_ = false;
		}
		break;
	case WeaponType::ShotGun:
		if (currentWeapon_->GetHavingBulletNum() <= 10)
		{
			addBlendFlag_ = true;
		}
		else
		{
			addBlendFlag_ = false;
		}
		break;

	case WeaponType::SubMachineGun:
		if (currentWeapon_->GetHavingBulletNum() <= 30)
		{
			addBlendFlag_ = true;
		}
		else
		{
			addBlendFlag_ = false;
		}
		break;
	default:
		break;
	}
	if (addBlendFlag_)
	{
		addBlendval_ -= 3;
		if (addBlendval_ <= 0)
		{
			addBlendval_ = 255;
		}
	}
	else
	{
		addBlendval_ = 255;
	}

	SetDrawBright(255, abs(addBlendval_), abs(addBlendval_));
	DrawRotaGraph(bulletNumPos_.x, bulletNumPos_.y, 1.0f, 0.0f,
		lpImage.GetDivID("UI/number")[currentWeapon_->GetHavingBulletNum() / 100], true, false);
	DrawRotaGraph(bulletNumPos_.x + 30, bulletNumPos_.y, 1.0f, 0.0f,
		lpImage.GetDivID("UI/number")[currentWeapon_->GetHavingBulletNum() % 100 / 10], true, false);
	DrawRotaGraph(bulletNumPos_.x + 60, bulletNumPos_.y, 1.0f, 0.0f,
		lpImage.GetDivID("UI/number")[currentWeapon_->GetHavingBulletNum() % 10], true, false);
	SetDrawBright(255, 255, 255);


	for (auto num : getBulletNumPos_)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, num.first.second);
		DrawRotaGraph(num.first.first.x, num.first.first.y, 1.0f, 0.0f,
			lpImage.GetDivID("UI/number")[num.second % 100 / 10], true, false);
		DrawRotaGraph(num.first.first.x + 25, num.first.first.y, 1.0f, 0.0f,
			lpImage.GetDivID("UI/number")[num.second % 10], true, false);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	}
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

	lpImage.LoadDiv("UI/weapons", Vector2I(110,64), Vector2I(1, 3));

	weaponsUIPos_ = { 90,160 };
	bulletNumPos_ = { weaponsUIPos_.x + 150,weaponsUIPos_.y + 30 };
	addBlendval_ = 255;
	addBlendFlag_ = false;
	Actor::Initialize();
	return true;
}

void ControlledPlayer::Walk(const Vector2I& speed, const int& zSp)
{
	pos_.x += speed.x;

	if (pos_.x <= 0)
	{
		pos_.x = 0;
	}
	if (pos_.x >= floorX - (size_.x / 2))
	{
		pos_.x = floorX - (size_.x / 2);
	}
	z_ += zSp;

	isOnFloor_ = true;

	if (z_ >= 0)
	{
		isOnFloor_ = false;
		z_ = 0;
	}
	if (z_ <= -floorZ)
	{
		isOnFloor_ = false;
		z_ = -floorZ;
	}
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

void ControlledPlayer::GetItems(void)
{
	for (auto item : items_)
	{
		if(CircleCollision()(type_, item->GetPos() - pos_,
			Vector2I(size_.x + item->GetSize(), size_.y + item->GetSize()),
			item->GetZPos() - z_))
		{
			if (currentWeapon_->GetcanSetBulletType() ==
				item->GetType())
			{
				getBulletNumPos_.emplace_back(std::make_pair
				(std::make_pair
				(Vector2I(weaponsUIPos_.x + 150,weaponsUIPos_.y + 20),255),
					item->GetBulletNum()));
				currentWeapon_->GetHavingBulletNum() += item->GetBulletNum();
				lpSound.Play(currentWeapon_->GetWeaponName() + "/get", DX_PLAYTYPE_BACK);
				item->Delete();
			}
		}
	}
}

//void ControlledPlayer::GetMoneys(void)
//{
//	for (auto money : moneyItems_)
//	{
//		if (CircleCollision()(type_, money->GetPos() - pos_,
//			Vector2I(size_.x + money->GetSize().x, size_.y + money->GetSize().y),
//			(money->GetZPos() - (z_ + 35))))
//		{
//			havingMoney_[static_cast<int>(money->GetType())] += money->GetMoneyRate(money->GetType());
//			lpSound.Play("money_get", DX_PLAYTYPE_BACK);
//			money->Delete();
//		}
//	}
//}
