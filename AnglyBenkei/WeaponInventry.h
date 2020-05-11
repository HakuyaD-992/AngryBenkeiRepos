#pragma once
#include <mutex>
#include <array>
#include "Vector2.h"
#include "GameController.h"
#include "WEAPON.h"

#define lpWeaponInventry WeaponInventry::getInstance()

// ²İÍŞİÄØ‚Ì“o˜^‡
enum WeaponInventoryNum
{
	W_Num_1,
	W_Num_2,
	W_Num_3,
	W_Num_4,
	W_Num_Max
};


class WeaponInventry
{
public:
	static void Destroy(void);
	static WeaponInventry &getInstance(void)
	{
		std::call_once(onceflag, Create);
		return *weaponIns;
	}

	// ²İÍŞİÄØ‚ÌÎß¼Ş¼®İ‚ğÌßÚ²Ô°‚ÌÎß¼Ş¼®İ‚É’Ç]
	void UpDateInventoryPos(const Vector2& pos);
	// ²İÍŞİÄØ‚Ì•`‰æ	
	void DrawInventory(const std::array<WEAPON,W_Num_Max> havingWeapon);
	// Œ»İ‘•”õ‚µ‚Ä‚¢‚é•Ší‚Ì•ÏX
	void ChangeWeaponNum(const GameController& gameCtl);
	// ¶°¿Ù‚Ì•`‰æ
	void DrawCursor(const Vector2& pos);
	// ¡Œ»İ‘I‘ğ‚µ‚Ä‚¢‚é•Ší”Ô†‚ğ•Ô‚·ŠÖ”
	const WeaponInventoryNum& GetCurrentWeaponNum(void)
	{
		return curWeapon;
	}

private:
	WeaponInventry();
	~WeaponInventry();

	static std::once_flag onceflag;
	static WeaponInventry* weaponIns;

	static void Create(void);



	// ²İÍŞİÄØ‚Ì˜g‚ÌÎß¼Ş¼®İ
	Vector2 inventoryFramePos[W_Num_Max];
	// ²İÍŞİÄØ‚Ì•Ší‚ğ‘I‚Ô‚½‚ß‚ÌŒˆ’è¶°¿Ù‚ÌÎß¼Ş¼®İ
	Vector2 cursorPos;
	// Œ»İ‘I‘ğ’†‚Ì•Ší”Ô†
	WeaponInventoryNum curWeapon;
};

