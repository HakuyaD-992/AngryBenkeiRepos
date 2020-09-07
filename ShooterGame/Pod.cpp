#include <DxLib.h>
#include "Pod.h"
#include "ControlledPlayer.h"
#include "WeaponBase.h"
#include "EnemyAIManager.h"
#include "PodAI.h"
#include "AICollider.h"
#include "EnemyBullet.h"
#include "ImageManager.h"

// Z座標を合わせる行動に移る距離
constexpr int arrangementZDistance = 150;

Pod::Pod(Vector2I pos,
	int z, 
	ActorType type,
	std::vector<std::shared_ptr<ControlledPlayer>>& player):
	Enemy(player)
{
	pos_ = pos;
	size_ = Vector2I(55,55);
	z_ = z;
	type_ = type;
	aiCollider_ = std::make_unique<AICollider>();
	aiSystem_ = std::make_shared<PodAI>(*this);

	hp_ = 5;

	lpImage.LoadDiv("podmuzzleFlash", Vector2I(55, 60), Vector2I(5, 1));
	Initialize();
	Actor::Initialize();
	ChangeAnimation("walk");

	updater_ = &Pod::Walk;
	id_ = enemyNo_;
	enemyNo_++;
}

Pod::~Pod()
{
}

void Pod::UpDate(void)
{
	gravity_->Apply(pos_);
	aiCollider_->SetPos(pos_,z_);

	// ｱﾆﾒｰｼｮﾝ
	UpDateAnimation(currentAnimation_);
}

void Pod::Draw_(void)
{
	Actor::Draw();
	if (isTurnLeft_)
	{
		muzzleFlashPos_ = Vector2I(pos_.x -40, pos_.y - 5 + (z_/2));
	}
	else
	{
		muzzleFlashPos_ = Vector2I(pos_.x +40, pos_.y - 5 + (z_ / 2));
	}
	if (currentAnimation_ == "attack_release")
	{
		DrawRotaGraph(muzzleFlashPos_.x, muzzleFlashPos_.y,
			1.0f, 0.0f, lpImage.GetDivID("podmuzzleFlash")[muzzleFlashAnimationCount_],
			true,isTurnLeft_,false);
	}
	DrawFormatString(300, 20, 0xffffff, currentAnimation_.c_str());
}

void Pod::Walk(void)
{
	if (pos_.x > GetNearestPlayer()->GetPos().x)
	{
		isTurnLeft_ = true;
		speed_.x = -2;
	}
	if (pos_.x < GetNearestPlayer()->GetPos().x)
	{
		isTurnLeft_ = false;
		speed_.x = 2;
	}

	pos_.x += speed_.x;
	// ここで距離の計算をやって、変数に入れている
	auto distance = GetNearestPlayer()->GetPos().x - pos_.x;

	// Podとプレイヤーとの距離が一定距離になれば
	// PodはプレイヤーのZ軸に合わせる行動をする
	if (abs(distance) < arrangementZDistance)
	{
		updater_ = &Pod::Z_Arrangement;
	}
}

void Pod::Z_Arrangement(void)
{
	if (isTurnLeft_)
	{
		speed_.x = -1;
	}
	else
	{
		speed_.x = 1;
	}

	auto playerZ = GetNearestPlayer()->GetZPos();

	if (z_ >= playerZ)
	{
		zSpeed_ = -1;
	}
	else
	{
		zSpeed_ = 1;
	}

	z_ += zSpeed_;
	
	if (abs(z_ - playerZ) <= 3)
	{
		ChangeAnimation("attack_prepare");
		updater_ = &Pod::Attack;
	}
}

void Pod::Attack(void)
{
	if (isAnimEnd_)
	{
		ChangeAnimation("attack_release");
	}

	if (currentAnimation_ == "attack_release")
	{
		if (isAnimEnd_)
		{
			ChangeAnimation("walk");
			updater_ = &Pod::Walk;
		}
	}

}

void Pod::Evacuate(void)
{
	auto playerZ = SearchNearestPlayer()->GetZPos();

	if (z_ <= playerZ)
	{
		zSpeed_ = 1;
	}
	else
	{
		zSpeed_ = -1;
	}

	z_ += zSpeed_;

	auto zdiff = playerZ - z_;

	if (abs(zdiff) >= 50)
	{
		ChangeAnimation("walk");
		updater_ = &Pod::Walk;
	}
}
