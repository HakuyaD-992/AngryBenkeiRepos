#pragma once
#include <mutex>
#include <array>
#include "Vector2.h"
#include "GameController.h"
#include "WEAPON.h"

#define lpWeaponInventry WeaponInventry::getInstance()

// ｲﾝﾍﾞﾝﾄﾘの登録順
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

	// ｲﾝﾍﾞﾝﾄﾘのﾎﾟｼﾞｼｮﾝをﾌﾟﾚｲﾔｰのﾎﾟｼﾞｼｮﾝに追従
	void UpDateInventoryPos(const Vector2& pos);
	// ｲﾝﾍﾞﾝﾄﾘの描画	
	void DrawInventory(const std::array<WEAPON,W_Num_Max> havingWeapon);
	// 現在装備している武器の変更
	void ChangeWeaponNum(const GameController& gameCtl);
	// ｶｰｿﾙの描画
	void DrawCursor(const Vector2& pos);
	// 今現在選択している武器番号を返す関数
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



	// ｲﾝﾍﾞﾝﾄﾘの枠のﾎﾟｼﾞｼｮﾝ
	Vector2 inventoryFramePos[W_Num_Max];
	// ｲﾝﾍﾞﾝﾄﾘの武器を選ぶための決定ｶｰｿﾙのﾎﾟｼﾞｼｮﾝ
	Vector2 cursorPos;
	// 現在選択中の武器番号
	WeaponInventoryNum curWeapon;
};

