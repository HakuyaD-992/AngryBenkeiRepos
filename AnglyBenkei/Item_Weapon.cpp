#include "Item_Weapon.h"
#include "BasePlayer.h"


Item_Weapon::Item_Weapon(Vector2 pos,Vector2 size,WEAPON type)
{
	this->pos = pos;
	this->size = size;
	weaponType = type;

	Init();
}


Item_Weapon::~Item_Weapon()
{
}

void Item_Weapon::Move(WeakList charaList)
{
	for (auto p = charaList.lock()->begin(); p != charaList.lock()->end(); p++)
	{
		// ������E����
		if (isHadbyPlayer)
		{
			// ������߼޼�݂���ڲ԰���߼޼�݂ɂ���
			pos = (*p)->GetPos();
		}
		if (isThrowAway)
		{
			isThrowMove = true;
		}
		else
		{
			jumpDir = (*p)->GetDirection();
		}
	}
	// �����яo��
	JumpFromPlayer();

	if (pos.y >= 500)
	{
		pos.y = 500;
		isThrowMove = false;
		isThrowAway = false;
	}
	if (pos.x >= lpScene.GetScreenSize().x)
	{
		jumpDir = Direction_Left;
	}
	if (pos.x <= 0)
	{
		jumpDir = Direction_Right;
	}
}

bool Item_Weapon::Init(void)
{
	ItemBase::Init("Image/weapon/weapon_All.png", size);
	moveF = false;
	return true;
}
