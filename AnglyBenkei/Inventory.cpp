#include <DxLib.h>

#include "Inventory.h"
#include "ImageManager.h"


Inventory::Inventory(WeaponInventoryNum inventoryNo,WEAPON type)
{
	this->inventoryNo = inventoryNo;
	this->hadWeaponType = type;
	Init();
}


Inventory::~Inventory()
{
}

void Inventory::Draw(void)
{
	// ˜g‚Ì•`‰æ
	DrawRotaGraph(framePos.x, framePos.y, 1.0f, 0.0f,
		lpImageMng.GetID("Image/WeaponInventory/inventoryFrame.png")[0], true, false);

	DrawRotaGraph(framePos.x, framePos.y, 1.0f, 0.0f,
		lpImageMng.GetID("Image/weapon/weapon_All.png")[hadWeaponType], true, false);
}

bool Inventory::Init(void)
{
	framePos = { 50 + (80 * inventoryNo),100 };
	lpImageMng.GetID("Image/WeaponInventory/inventoryFrame.png");
	lpImageMng.GetID("Image/weapon/weapon_All.png", Vector2(50, 50), Vector2(3, 3));
	return true;
}

void Inventory::Add(WEAPON & addWeapon)
{
	hadWeaponType = addWeapon;
}
