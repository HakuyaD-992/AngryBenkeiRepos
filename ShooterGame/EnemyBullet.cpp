#include <DxLib.h>
#include "EnemyBullet.h"
#include "ImageManager.h"
#include "EffectManager.h"
#include "Floor.h"
#include "SoundManager.h"

int EnemyBullet::no_ = 0;

EnemyBullet::EnemyBullet(Vector2I pos, int z, const ActorType& actor, bool isLeft)
{
	z_ = z;
	isMoveLeft_ = isLeft;
	extendFlag_ = false;
	switch (actor)
	{
	case ActorType::Pod:
		type_ = BulletType::PodBullet;
		bulletName_ = "podbullet";
		isMove_ = true;
		exRate_ = 1.0f;
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
		Initialize();

		break;
		case ActorType::Exoskeleton:

		break;
		case ActorType::Spacenaut:
			type_ = BulletType::SpacenautBullet;
			isMove_ = true;
			exRate_ = 1.0f;
			bulletName_ = "pistolbullet";
			size_ = Vector2I(8, 4);
			if (isLeft)
			{
				pos_ = Vector2I(pos.x - 20, pos.y + 7);
				speed_ = -4.0f;
			}
			else
			{
				pos_ = Vector2I(pos.x + 20, pos.y +7);
				speed_ = 4.0f;
			}
			Initialize();

			break;
		case ActorType::Bigboy:
			type_ = BulletType::BossBullet;
			isMove_ = false;
			exRate_ = 0.0f;
			size_ = Vector2I(0, 100);
			bulletName_ = "bossbullet";
			if (isLeft)
			{
				pos_ = Vector2I(pos.x + 150, pos.y - 10);
				speed_ = 7.0f;
			}
			else
			{
				pos_ = Vector2I(pos.x - 150, pos.y - 10);
				speed_ = -7.0f;
			}
			Initialize();

			break;
	default:
		break;
	}

	SetAnimation("non");
}

EnemyBullet::~EnemyBullet()
{
}

void EnemyBullet::UpDate(void)
{
	if (type_ == BulletType::BossBullet)
	{
		if (!isMove_)
		{
			if (!extendFlag_)
			{
				lpSound.Play("Bigboy/charge", DX_PLAYTYPE_BACK);
				extendFlag_ = true;
			}
			exRate_ += 0.03f;
			if (exRate_ >= 2.0f)
			{
				exRate_ = 2.0f;
				lpSound.Stop("Bigboy/charge");
				lpSound.Play("Bigboy/fire", DX_PLAYTYPE_BACK);
				isMove_ = true;
				extendFlag_ = false;
			}
		}
		animationCount_ += 1.0f;
		if (animationCount_ >= 19.0f)
		{
			animationCount_ = 0.0f;
		}
	}
	if (isMove_)
	{
		pos_.x += speed_;
	}

	if (pos_.x <= 0 || pos_.x >= floorX - (size_.x / 2))
	{
		Delete();
	}
}

void EnemyBullet::Draw(void)
{
	auto& imageMng = ImageManager::GetInstance();

	drawPos_ = Vector2I(pos_.x, pos_.y + (z_ / 2));

	DrawRotaGraph(drawPos_.x, drawPos_.y,
		exRate_, rotRate_,
		imageMng.GetBulletResource(type_).imageHandle_.find(currentAnimation_)->second[animationCount_],
		true, false);
}

bool EnemyBullet::Initialize(void)
{
	auto& imageMng = ImageManager::GetInstance();
	imageMng.LoadBullet(type_, bulletName_);

	return true;
}

void EnemyBullet::UpDateAnimation(std::string animName)
{
}
