#include <DxLib.h>
#include "EnemyBullet.h"
#include "ImageManager.h"
#include "EffectManager.h"

EnemyBullet::EnemyBullet(Vector2I pos, int z, const ActorType& actor, bool isLeft)
{
	z_ = z;
	isMoveLeft_ = isLeft;
	switch (actor)
	{
	case ActorType::Pod:
		type_ = BulletType::PodBullet;
		bulletName_ = "podbullet";
		size_ = Vector2I(8, 8);
		if (isLeft)
		{
			pos_ = Vector2I(pos.x - 20, pos.y - 3);
			speed_ = -4.0f;
		}
		else
		{
			pos_ = Vector2I(pos.x + 20, pos.y - 3);
			speed_ = 4.0f;
		}
		break;
		case ActorType::Exoskeleton:

		break;
		case ActorType::Spacenaut:
			type_ = BulletType::SpacenautBullet;
			bulletName_ = "pistolbullet";
			size_ = Vector2I(8, 4);
			if (isLeft)
			{
				pos_ = Vector2I(pos.x - 20, pos.y - 3);
				speed_ = -4.0f;
			}
			else
			{
				pos_ = Vector2I(pos.x + 20, pos.y - 3);
				speed_ = 4.0f;
			}
			break;
		case ActorType::Bigboy:
			pos_ = Vector2I(pos.x, pos.y - 10);
			type_ = BulletType::LaserBullet;
			size_ = Vector2I(0, 100);
			if (isLeft)
			{
				bulletName_ = "laserRight";
			}
			else
			{
				bulletName_ = "laserLeft";
			}
			break;

	default:
		break;
	}

	Initialize();
	SetAnimation("non");
}

EnemyBullet::~EnemyBullet()
{
}

void EnemyBullet::UpDate(void)
{
	pos_.x += speed_;

}

void EnemyBullet::Draw(void)
{
	auto& imageMng = ImageManager::GetInstance();

	drawPos_ = Vector2I(pos_.x, pos_.y + (z_ / 2));

	if (type_ != BulletType::LaserBullet)
	{
		DrawRotaGraph(drawPos_.x, drawPos_.y,
			exRate_, rotRate_,
			imageMng.GetBulletResource(type_).imageHandle_.find(currentAnimation_)->second[animationCount_],
			true, false);
	}
	else
	{
		lpEffect.Draw();
	}
}

bool EnemyBullet::Initialize(void)
{
	auto& imageMng = ImageManager::GetInstance();
	if (type_ != BulletType::LaserBullet)
	{
		imageMng.LoadBullet(type_, bulletName_);
	}
	else
	{
		lpEffect.Load(bulletName_);
	}
	return true;
}

void EnemyBullet::UpDateAnimation(std::string animName)
{
}
