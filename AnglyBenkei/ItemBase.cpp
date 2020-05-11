#include <DxLib.h>

#include "ItemBase.h"


ItemBase::ItemBase()
{
	deleteFlag = false;
	isHadbyPlayer = false;
	isThrowAway = false;
	isThrowMove = false;
	addInventoryFlag = false;

	// 武器飛び出し関係
	startingJumpSpeed = -5.0f;
	jumpForce = 0.0f;

	myInventoryNum = W_Num_Max;
	// 重力のｲﾝｽﾀﾝｽ
	gravity = new Gravity();
}

ItemBase::~ItemBase()
{
}

void ItemBase::UpDate(WeakList charaList)
{
	Move(charaList);
}

void ItemBase::Draw(void)
{
	if (!isHadbyPlayer)
	{
		DrawRotaGraph(pos.x, pos.y,
			1.0f, 0.0f,
			lpImageMng.GetID(imageName)[weaponType],
			true, false);
	}
	DrawCircle(pos.x, pos.y, 3, 0xff0000, true);
	DrawFormatString(340, 50 + (50 * weaponType), 0xffffff, "(x:%d,y:%d)", pos.x, pos.y);

	DrawFormatString(50,50 + (50 * weaponType), 0xffffff, "%d", myInventoryNum);
	
	if (isThrowMove)
	{
		DrawFormatString(300, 50 + (50 * weaponType), 0xffffff, "Jump");
	}
	else
	{
		DrawFormatString(300, 50 + (50 * weaponType), 0xffffff, "No");
	}

	if (isHadbyPlayer)
	{
		DrawFormatString(100, 50 + (50 * weaponType), 0xffffff, "isHadbyPlayer");
	}
	else
	{
		DrawFormatString(100, 50 + (50 * weaponType), 0xffffff, "is'Not'HadbyPlayer");
	}
}

bool ItemBase::Init(std::string imgName,Vector2 size)
{
	imageName = imgName;
	this->size = size;
	lpImageMng.GetID(imgName, size, Vector2(3, 3));
	return true;
}

void ItemBase::CalcDistance(const Vector2 & pos)
{
	distance = pos - this->pos;

	// 距離変数をｸﾗﾝﾌﾟ---------------------
	if (distance.x < 0)
	{
		distance.x = distance.x * (-1);
	}
	else
	{
		distance.x = distance.x * 1;
	}
	if (distance.y < 0)
	{
		distance.y = distance.y * (-1);
	}
	else
	{
		distance.y = distance.y * 1;
	}
	//------------------------------------------
}

bool ItemBase::IsHit(const Vector2 & size)
{
	if (distance.x <= ((this->size.x / 2) + (size.x / 2)) &&
		distance.y <= ((this->size.y / 2) + (size.y / 2)))
	{
		return true;
	}
	return false;
}

void ItemBase::SetInventoryNum(const WeaponInventoryNum & wNum)
{
	myInventoryNum = wNum;
}

void ItemBase::JumpFromPlayer(void)
{
	// 飛び出しの時はｼﾞｬﾝﾌﾟに重力を加える
	if (isThrowMove)
	{
		jumpForce = startingJumpSpeed;

		pos.y += jumpForce;
		switch (jumpDir)
		{
		case Direction_Right:
			pos.x += 3;
			break;

		case Direction_Left:
			pos.x -= 3;
			break;
		default:
			break;
		}
		startingJumpSpeed += GRAVITY;
	}
	// 飛び出していない時は武器自体に重力をかける
	else
	{
		gravity->PutGravityOnActor(pos);
		startingJumpSpeed = -5.0f;
	}


}
