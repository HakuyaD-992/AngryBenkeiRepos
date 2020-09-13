#include <DxLib.h>
#include "EnemyBullet.h"
#include "ImageManager.h"
#include "EffectManager.h"
#include "Floor.h"
#include "SoundManager.h"
#include "Enemy.h"

int EnemyBullet::no_ = 0;

EnemyBullet::EnemyBullet(Vector2I pos, int z, const ActorType& actor,
	bool isLeft,Enemy& enemy):
	enemy_(enemy)
{
	z_ = z;
	bulletExplosionCnt_ = 0.0f;
	isMoveLeft_ = isLeft;
	extendFlag_ = false;
	level_ = enemy.GetLevel();
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
		BulletBase::Initialize();

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
			BulletBase::Initialize();

			break;
		case ActorType::Bigboy:
			type_ = BulletType::BossBullet;
			isMove_ = false;
			exRate_ = 0.0f;
			size_ = Vector2I(60, 60);
			bulletName_ = "bossbullet";
			if (isLeft)
			{
				pos_ = Vector2I(pos.x + 150, pos.y - 10);
				switch (level_)
				{
				case Level::Lv_1:
					speed_ = 7.0f;
					break;

				case Level::Lv_2:
					speed_ = 3.0f;
					break;

				case Level::Lv_3:
					speed_ = 3.0f;
					break;
				case Level::Max:
					break;
				default:
					break;
				}
			}
			else
			{
				pos_ = Vector2I(pos.x - 150, pos.y - 10);
				switch (enemy_.GetLevel())
				{
				case Level::Lv_1:
					speed_ = -7.0f;

					break;

				case Level::Lv_2:
					speed_ = -3.0f;
					break;

				case Level::Lv_3:
					speed_ = -3.0f;
					break;
				case Level::Max:

					break;
				default:
					break;
				}
			}
			BulletBase::Initialize();

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
		if (isMove_)
		{
			switch (level_)
			{
			case Level::Lv_1:
				break;

			case Level::Lv_2:
				bulletExplosionCnt_ += 1.5f;
				if (bulletExplosionCnt_ >= 85.0f)
				{
					if (!isShake_)
					{
						isShake_ = true;
						lpSound.Play("explosionboss", DX_PLAYTYPE_BACK);
					}
					SetAnimation("explosion");
					if (isAnimEnd_)
					{
						Delete();
					}
				}

				break;

			case Level::Lv_3:

				break;
			case Level::Max:

				break;
			default:
				break;
			}
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
	UpDateAnimation(currentAnimation_);
}

void EnemyBullet::Draw(void)
{
	auto& imageMng = ImageManager::GetInstance();

	BulletBase::Draw();

	drawPos_ = Vector2I(pos_.x, pos_.y + (z_ / 2));

	DrawRotaGraph(drawPos_.x, drawPos_.y,
		exRate_, rotRate_,
		imageMng.GetBulletResource(type_).imageHandle_.find(currentAnimation_)->second[animationCount_],
		true, false);
}

void EnemyBullet::UpDateAnimation(std::string animName)
{
	if (type_ == BulletType::BossBullet)
	{
		if (animName != "explosion")
		{
			animationCount_ += 1.0f;
		}
		else
		{
			animationCount_ += 0.3f;
		}
	}
	else
	{
		animationCount_ += 1.0f;
	}

	if (animationSet_.find(animName) != animationSet_.end())
	{
		if ((int)animationCount_ >= animationSet_.find(animName)->second)
		{
			if (isLoop_[animName])
			{
				animationCount_ = 0.0f;
			}
			else
			{
				animationCount_ = animationSet_.find(animName)->second;
				isAnimEnd_ = true;
			}
		}
	}
}
