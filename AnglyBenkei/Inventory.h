#pragma once
#include "WeaponInventry.h"
#include "WEAPON.h"
#include "Vector2.h"

class Inventory
{
public:
	Inventory(WeaponInventoryNum inventoryNo,WEAPON type);
	~Inventory();

	void Draw(void);
	bool Init(void);

	void Add(WEAPON& addWeapon);

	WEAPON& GetWeaponType(void)
	{
		return hadWeaponType;
	}

	const Vector2& GetFramePos(void)
	{
		return framePos;
	}

private:
	WeaponInventoryNum inventoryNo;
	Vector2 framePos;

	WEAPON hadWeaponType;
};

