#include <DxLib.h>

#include "WeaponInventry.h"
#include "ImageManager.h"

std::once_flag WeaponInventry::onceflag;
WeaponInventry* WeaponInventry::weaponIns = nullptr;

void WeaponInventry::Destroy(void)
{
	if (weaponIns != nullptr)
	{
		delete weaponIns;
	}
	weaponIns = nullptr;
}

void WeaponInventry::UpDateInventoryPos(const Vector2 & pos)
{
	// ｲﾝﾍﾞﾝﾄﾘのﾎﾟｼﾞｼｮﾝを少しづつずらしている
	/*for (int w = W_Num_1; w < W_Num_Max; w++)
	{
		inventoryFramePos[w].x = (pos.x + 30) - (w * 5);
		inventoryFramePos[w].y = (pos.y - 80) + (w * 5);
	}*/
}

void WeaponInventry::DrawInventory(const std::array<WEAPON,W_Num_Max> havingWeapon)
{
	// ｲﾝﾍﾞﾝﾄﾘの枠の描画
	for (int w = W_Num_1; w < W_Num_Max; w++)
	{
		DrawRotaGraph(inventoryFramePos[w].x, inventoryFramePos[w].y,
			1.0f, 0.0f, lpImageMng.GetID("Image/WeaponInventory/inventoryFrame.png")[0],
			true, false);
	}
	for (int w = W_Num_1; w < W_Num_Max; w++)
	{
		// 武器を所持したら、そこに所持武器ｱｲｺﾝ描画
		DrawRotaGraph(inventoryFramePos[w].x, inventoryFramePos[w].y,
			1.0f, 0.0f, lpImageMng.GetID("Image/weapon/weapon_All.png")[havingWeapon[w]],
			true, false);
	}
}

void WeaponInventry::ChangeWeaponNum(const GameController & gameCtl)
{
	auto padNow = gameCtl.GetPadInfo().padInputNow;
	auto padOld = gameCtl.GetPadInfo().padInputOld;

	// ｶｰｿﾙの位置移動-----------------------------
	if (padNow[9] && !padOld[9])
	{
		cursorPos.x += 80;
		if (cursorPos.x >= inventoryFramePos[W_Num_4].x)
		{
			cursorPos.x = inventoryFramePos[W_Num_4].x;
		}
	}
	if (padNow[8] && !padOld[8])
	{
		cursorPos.x -= 80;
		if (cursorPos.x <= inventoryFramePos[W_Num_1].x)
		{
			cursorPos.x = inventoryFramePos[W_Num_1].x;
		}
	}
	//---------------------------------------------

	// 現在装備している武器の武器番号の変更-----------------
	if (cursorPos == inventoryFramePos[W_Num_1])
	{
		curWeapon = W_Num_1;
	}
	if (cursorPos == inventoryFramePos[W_Num_2])
	{
		curWeapon = W_Num_2;
	}
	if (cursorPos == inventoryFramePos[W_Num_3])
	{
		curWeapon = W_Num_3;
	}
	if (cursorPos == inventoryFramePos[W_Num_4])
	{
		curWeapon = W_Num_4;
	}
	//------------------------------------------------------
}

void WeaponInventry::DrawCursor(const Vector2& pos)
{
	DrawRotaGraph(pos.x, pos.y,
				  1.0f, 0.0f, lpImageMng.GetID("Image/WeaponInventory/cursor.png")[0],
				  true, false);
}

WeaponInventry::WeaponInventry()
{
	// ｲﾝﾍﾞﾝﾄﾘの枠画像のﾛｰﾄﾞ
	lpImageMng.GetID("Image/WeaponInventory/inventoryFrame.png");
	// ｶｰｿﾙの画像ﾛｰﾄﾞ
	lpImageMng.GetID("Image/WeaponInventory/cursor.png");
	// 武器の画像ﾛｰﾄﾞ
	lpImageMng.GetID("Image/weapon/weapon_All.png", Vector2(50, 50), Vector2(3, 3));
	for (int w = W_Num_1; w < W_Num_Max; w++)
	{
		inventoryFramePos[w].x = 50 + (w * 80);
		inventoryFramePos[w].y = 50;
	}

	cursorPos = inventoryFramePos[W_Num_1];
	curWeapon = W_Num_1;
}


WeaponInventry::~WeaponInventry()
{
}

void WeaponInventry::Create(void)
{
	weaponIns = new WeaponInventry();
}
