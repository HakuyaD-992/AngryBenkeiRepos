#include <DxLib.h>
#include "PlayerBullet.h"
#include "ImageManager.h"

PlayerBullet::PlayerBullet(Vector2I pos,int z,WeaponType weapon,bool isLeft)
{
	z_ = z;
	isMoveLeft_ = isLeft;
	switch (weapon)
	{
	case WeaponType::Pistol:
		type_ = BulletType::PistolBullet;
		bulletName_ = "pistolbullet";
		size_ = Vector2I(8, 4);
		if (isLeft)
		{
			pos_ = Vector2I(pos.x - 20, pos.y-3);
			speed_ = -4.0f;
		}
		else
		{
			pos_ = Vector2I(pos.x + 20, pos.y-3);
			speed_ = 4.0f;
		}
		break;
	case WeaponType::ShotGun:
		type_ = BulletType::ShotBullet;
		bulletName_ = "shotbullet";
		size_ = Vector2I(64, 64);
		if (isLeft)
		{
			pos_ = Vector2I(pos.x - 20, pos.y);
			speed_ = -4.0f;
		}
		else
		{
			pos_ = Vector2I(pos.x + 20, pos.y);
			speed_ = 4.0f;
		}
		break;
	case WeaponType::SubMachineGun:
		type_ = BulletType::MachineBullet;
		bulletName_ = "machinebullet";
		size_ = Vector2I(8,3);
		if (isLeft)
		{
			pos_ = Vector2I(pos.x - 20, pos.y -3);
			speed_ = -4.0f;
		}
		else
		{
			pos_ = Vector2I(pos.x + 20, pos.y - 3);
			speed_ = 4.0f;
		}
		break;
	case WeaponType::Max:
		break;
	default:
		break;
	}

	Initialize();
	SetAnimation("non");
}

PlayerBullet::~PlayerBullet()
{
}

void PlayerBullet::UpDate(void)
{
	pos_.x += speed_;
}

void PlayerBullet::Draw(void)
{
	auto& imageMng = ImageManager::GetInstance();

	drawPos_ = Vector2I(pos_.x, pos_.y + (z_ / 2));

	DrawRotaGraph(drawPos_.x, drawPos_.y,
		exRate_, rotRate_,
		imageMng.GetBulletResource(type_).imageHandle_.find(currentAnimation_)->second[animationCount_],
		true, false);
}

void PlayerBullet::UpDateAnimation(std::string animName)
{
}

bool PlayerBullet::Initialize(void)
{
	auto& imageMng = ImageManager::GetInstance();

	imageMng.LoadBullet(type_, bulletName_);

	return true;
}
