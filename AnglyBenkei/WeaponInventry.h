#pragma once
#include <mutex>
#include <array>
#include "Vector2.h"
#include "GameController.h"
#include "WEAPON.h"

#define lpWeaponInventry WeaponInventry::getInstance()

// ������؂̓o�^��
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

	// ������؂��߼޼�݂���ڲ԰���߼޼�݂ɒǏ]
	void UpDateInventoryPos(const Vector2& pos);
	// ������؂̕`��	
	void DrawInventory(const std::array<WEAPON,W_Num_Max> havingWeapon);
	// ���ݑ������Ă��镐��̕ύX
	void ChangeWeaponNum(const GameController& gameCtl);
	// ���ق̕`��
	void DrawCursor(const Vector2& pos);
	// �����ݑI�����Ă��镐��ԍ���Ԃ��֐�
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



	// ������؂̘g���߼޼��
	Vector2 inventoryFramePos[W_Num_Max];
	// ������؂̕����I�Ԃ��߂̌��趰�ق��߼޼��
	Vector2 cursorPos;
	// ���ݑI�𒆂̕���ԍ�
	WeaponInventoryNum curWeapon;
};

