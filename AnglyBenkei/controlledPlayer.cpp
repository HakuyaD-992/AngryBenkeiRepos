#include <DxLib.h>

#include "controlledPlayer.h"
#include "Item_Weapon.h"



controlledPlayer::controlledPlayer(Vector2 pos,ANIMATION anim,Vector2 size)
{
	this->pos = pos;
	this->size = size;
	this->myActionType = anim;
	Init();
}


controlledPlayer::~controlledPlayer()
{
}

void controlledPlayer::Draw(void)
{
	BasePlayer::Draw();

	// 武器ｲﾝﾍﾞﾝﾄﾘの描画
	for (int w = W_Num_1; w < W_Num_Max; w++)
	{
		inventory[w]->Draw();
	}
	lpWeaponInventry.DrawCursor(inventory[lpWeaponInventry.GetCurrentWeaponNum()]->GetFramePos());
}

void controlledPlayer::Init(void)
{
	for (int weapon = WEAPON_SWORD; weapon < WEAPON_MAX; weapon++)
	{
		InitAnimation((WEAPON)weapon);
	}
	

	oldAttackCount = 0;
}

void controlledPlayer::Action(const GameController & gameCtl, WeakWeaponList item)
{
	auto inputNow = gameCtl.GetPadInfo().padInputNow;
	auto inputOld = gameCtl.GetPadInfo().padInputOld;

	// 重力をかける
	gravity->PutGravityOnActor(pos);

	// 武器の変更
	lpWeaponInventry.ChangeWeaponNum(gameCtl);

	// 床にいる場合
	if (pos.y >= 500)
	{
		pos.y = 500;
	}

	// ｱｲﾃﾑとの当たり判定、ここから
	for (auto i = item.lock()->begin(); i != item.lock()->end(); i++)
	{
		// 距離計算
		(*i)->CalcDistance(pos);
		isHit = (*i)->IsHit(size);
		if (isHit)
		{
			// 当たっただけだとまだ追加ﾌﾗｸﾞはfalseのまま
			(*i)->GetAddInventoryFlag() = false;
			if (!(*i)->GetisHadbyPlayer())
			{
				// 下ｷｰを押すと拾うﾓｰｼｮﾝ
				if (inputNow[0] && !inputOld[0])
				{
					myActionType = ANIM_PICKUP;
					if (inventory[registerNum]->GetWeaponType() == WEAPON_NONE)
					{
						// 武器情報を格納
						inventory[registerNum]->Add((*i)->GetWeaponType());
						// 取得した武器にｲﾝﾍﾞﾝﾄﾘ番号を割り振る
						(*i)->SetInventoryNum(registerNum);
						// 1つ武器が格納されたら位置をずらす
						registerNum = (WeaponInventoryNum)(registerNum + 1);
						if (registerNum >= W_Num_4)
						{
							registerNum = W_Num_4;
						}

						// 武器ｱｲﾃﾑがﾌﾟﾚｲﾔｰから取得されたﾌﾗｸﾞをtrueに
						(*i)->GetisHadbyPlayer() = true;
						break;
					}
					else
					{
						// 現在指定している武器ｲﾝﾍﾞﾝﾄﾘがすでに埋まっていたら
						if (inventory[lpWeaponInventry.GetCurrentWeaponNum()]->GetWeaponType()
							!= WEAPON_NONE)
						{
							// 現在指定しているｲﾝﾍﾞﾝﾄﾘに新たに取得した武器ﾀｲﾌﾟを格納
							inventory[lpWeaponInventry.GetCurrentWeaponNum()]->Add((*i)->GetWeaponType());
							throwAwayFlag[lpWeaponInventry.GetCurrentWeaponNum()] = true;
							(*i)->GetAddInventoryFlag() = true;
							break;
						}
					}
				}
				else
				{
					throwAwayFlag[lpWeaponInventry.GetCurrentWeaponNum()] = false;
				}
			}
		}
	}

	// 武器を捨てて新しい武器を格納する処理
	if (throwAwayFlag[lpWeaponInventry.GetCurrentWeaponNum()])
	{
		for (auto i = item.lock()->begin(); i != item.lock()->end(); i++)
		{
			if ((*i)->GetInventoryNum() == lpWeaponInventry.GetCurrentWeaponNum())
			{
				(*i)->GetisThrowAway() = true;
				(*i)->SetInventoryNum(W_Num_Max);
				(*i)->GetisHadbyPlayer() = false;
			}
			if ((*i)->GetAddInventoryFlag())
			{
				(*i)->SetInventoryNum(lpWeaponInventry.GetCurrentWeaponNum());
				(*i)->GetisHadbyPlayer() = true;
			}
		}
	}


	// ﾀﾞｯｼｭ----------------------------------
	if (inputNow[2] && !inputOld[2])
	{
		isDash = true;
		direction = Direction_Right;
	}

	if (inputNow[1] && !inputOld[1])
	{
		isDash = true;
		direction = Direction_Left;
	}

	// ｶﾞｰﾄﾞ------------------------------
	if (inputNow[7])
	{
		// ﾎﾞﾀﾝを押している間、ｶﾞｰﾄﾞするｶｳﾝﾄ変数を加算
		guardTime++;
	}
	// ﾎﾞﾀﾝを押していないとｶｳﾝﾄ変数は0に戻る
	else
	{
		guardTime = 0;
	}

	// ｶﾞｰﾄﾞしている時間が0以上=ﾎﾞﾀﾝを押している時間だけｶﾞｰﾄﾞをする
	if (guardTime > 0)
	{
		myActionType = ANIM_GUARD;
	}
	// ﾎﾞﾀﾝを押していない時はｶﾞｰﾄﾞｶｳﾝﾄ変数は0に戻るのでwaitに戻す
	else
	{
		myActionType = ANIM_WAIT;
	}

	// 攻撃ｱﾆﾒｰｼｮﾝから(5/8夜勤の休憩の時)
	if (inputNow[5] && !inputOld[5])
	{
		attackFlag[inventory[lpWeaponInventry.GetCurrentWeaponNum()]->GetWeaponType()] = true;
	}
	if (attackFlag[inventory[lpWeaponInventry.GetCurrentWeaponNum()]->GetWeaponType()])
	{

	}

	// 決定ﾎﾞﾀﾝを押すと今現在指定している武器に変更するか検討

	if (isDash)
	{
		myActionType = ANIM_DASH;
		switch (direction)
		{
		case Direction_Right:
			pos.x += Speed;
			if (pos.x >= lpScene.GetScreenSize().x)
			{
				pos.x = lpScene.GetScreenSize().x;
			}
			break;
		case Direction_Left:
			pos.x -= Speed;
			if (pos.x <= 0)
			{
				pos.x = 0;
			}
			break;
		default:
			break;
		}
		dashTime--;
		if (dashTime <= 0)
		{
			isDash = false;
			dashTime = DashDefTime;
		}
	}

	// 自分のactionType毎にｱﾆﾒｰｼｮﾝを変更していく
	SetAnimation(lpImageMng.GetAnimString()[myActionType]);

	// 武器ｱｲｺﾝのﾎﾟｼﾞｼｮﾝをﾌﾟﾚｲﾔｰに追従
	lpWeaponInventry.UpDateInventoryPos(pos);
	//----------------------------------------
}

bool controlledPlayer::InitAnimation(WEAPON weapon)
{
	switch (weapon)
	{
	case WEAPON_SWORD:
		AddAnimation("attack", 9, 30, true, weapon);
		attackLevel[weapon] = { 3,6,9 };

		attackFlag[weapon]=false;
		break;
	case WEAPON_SPEAR:
		break;

	case WEAPON_AXE:
		break;
	case WEAPON_HAMMER:
		break;

	case WEAPON_TONGFAR:
		break;
	case WEAPON_JITTE:
		break;

	case WEAPON_NAGINATA:
		break;

	case WEAPON_NONE:

		break;
	default:
		break;
	}
	// 待ちﾓｰｼｮﾝ追加
	AddAnimation("wait", 5, 9, true, weapon);
	// ﾀﾞｯｼｭﾓｰｼｮﾝ追加
	AddAnimation("dash", 2, 10, false, weapon);
	// ｶﾞｰﾄﾞﾓｰｼｮﾝ追加
	AddAnimation("guard", 1, 10, true, weapon);
	// 拾いﾓｰｼｮﾝ追加
	AddAnimation("pickup", 5, 5, false, weapon);
	return true;
}
