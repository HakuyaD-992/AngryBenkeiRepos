#include <DxLib.h>
#include "Item.h"
#include "ScreenEffectMng.h"
#include "ImageManager.h"

Item::Item(const Vector2I& pos,const int& z, const BulletType& type)
{
	pos_ = pos;
	z_ = z;
	size_ = 32;
	type_ = type;

	Initialize();
}

Item::~Item()
{
}

void Item::UpDate(void)
{
	if (dropFlag_)
	{
		dropForce_ += 0.3f;
		dropSpeed_ = dropFirstSpeed_ + dropForce_;

		pos_.y += dropSpeed_;
	}
	else
	{
		existLimCount_ += 0.5f;
		if (existLimCount_ >= 200.0f)
		{
			flickCount_++;
		}

		if (eraseFlag_)
		{
			alphaval_--;
		}
		else if (flickCount_ >= 300)
		{
			eraseFlag_ = true;
			flickCount_ = 0;
		}
		if (alphaval_ <= 0)
		{
			alphaval_ = 0;
			Delete();
		}
	}

	if (dropSpeed_ >= 4.0f)
	{
		dropFirstSpeed_ = -3.0f;
		dropForce_ = 0.0f;
		dropSpeed_ = 0.0f;
		dropFlag_ = false;
	}
}

void Item::Draw(void)
{
	if (flickCount_ % 30 / 10 == 0)
	{
		lpS_Effect.DrawRotaAlphaGraph(Vector2I(pos_.x, pos_.y + (z_ / 2)),
			alphaval_, exRate_, imageHandle_);
	}
}

bool Item::Initialize(void)
{
	imageHandle_ = lpImage.GetDivID("Item/items")[static_cast<int>(type_)];
	alphaval_ = 255;
	exRate_ = 1.0f;

	switch (type_)
	{
	case BulletType::PistolBullet:
		bulletNum_ = 3;
		break;
	case BulletType::ShotBullet:
		bulletNum_ = 2;
		break;
	case BulletType::MachineBullet:
		bulletNum_ = 50;
		break;
	case BulletType::Max:
		break;
	default:
		break;
	}

	existLimCount_ = 0.0f;

	dropFirstSpeed_ = -3.0f;
	dropForce_ = 0.0f;
	dropSpeed_ = 0.0f;
	dropFlag_ = true;
	deleteFlag_ = false;
	eraseFlag_ = false;
	flickCount_ = 0.0f;

	return true;
}

bool Item::OnFloor(void)
{
	if (pos_.y >= 500)
	{
		return true;
	}
	return false;
}
