#include <DxLib.h>
#include "MoneyItem.h"
#include "ImageManager.h"
#include "Floor.h"

MoneyItem::MoneyItem(const Vector2I& pos, const int& z, MoneyType type)
{
	pos_ = pos;
	z_ = z;
	type_ = type;

	gravity_ = new Gravity();

	dropFirstSpeed_ = Vector2I(-4 + GetRand(8),-1+GetRand(-4));
	dropForce_ = Vector2I(0, 0);
	dropSpeed_ = Vector2I(0, 0);
	switch (type_)
	{
	case MoneyType::Gold:
		name_ = "Gold";
		break;
	case MoneyType::Platinum:
		name_ = "Platinum";
		break;
	case MoneyType::Red:
		name_ = "Red";
		break;
	case MoneyType::Max:
		break;
	default:
		break;
	}

	size_ = { 16,16 };

	Initialize();
}

MoneyItem::~MoneyItem()
{
}

void MoneyItem::Update(void)
{
	if (dropFlag_)
	{
		dropForce_.x += 0.3f;
		dropForce_.y += 0.3f;
		dropSpeed_ = dropFirstSpeed_ + dropForce_;

		pos_.x += dropSpeed_.x;
		pos_.y += dropSpeed_.y;
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
	gravity_->Apply(pos_);
	if (OnFloor())
	{
		dropFirstSpeed_ = Vector2I(0,0);
		dropForce_ = Vector2I(0,0);
		dropSpeed_ = Vector2I(0,0);
		dropFlag_ = false;
	}

	UpdateAnimation();
}

bool MoneyItem::Initialize(void)
{
	lpImage.LoadDiv("Item/Money_" + name_, size_, Vector2I(5,1));

	dropFlag_ = true;
	deleteFlag_ = false;
	eraseFlag_ = false;
	flickCount_ = 0.0f;

	existLimCount_ = 0.0f;

	alphaval_ = 255;
	exRate_ = 1.0f;

	moneyRate_ = 0;
	animationCount_ = 0.0f;

	return true;
}

void MoneyItem::Draw(void)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 80);
	DrawOvalAA(pos_.x, pos_.y + (z_ / 2) + (size_.y / 2), size_.x, size_.y / 2, 10, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawRotaGraph(pos_.x, pos_.y + (z_ / 2), exRate_, 0.0f,
		lpImage.GetDivID("Item/Money_" + name_)[animationCount_], true, false);


	DrawCircle(pos_.x, pos_.y + (z_ / 2), 3, 0xff0000, true);
	DrawFormatString(200, 200, 0xffffff, "z:%d", z_);
}

bool MoneyItem::OnFloor(void)
{
	if (pos_.y >= 500)
	{
		return true;
	}
	return false;
}

const int& MoneyItem::GetMoneyRate(const MoneyType& type)
{
	switch (type)
	{
	case MoneyType::Gold:
		moneyRate_ = 200;
		break;

	case MoneyType::Platinum:
		moneyRate_ = 500;
		break;

	case MoneyType::Red:
		moneyRate_ = 1000;
		break;
	default:
		break;
	}
	return moneyRate_;
}

void MoneyItem::UpdateAnimation(void)
{
	animationCount_ += 0.4f;

	if (animationCount_ > 5.0f)
	{
		animationCount_ = 0.0f;
	}


}
