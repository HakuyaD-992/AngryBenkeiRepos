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

	// ïêäÌ≤›Õﬁ›ƒÿÇÃï`âÊ
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

	// èdóÕÇÇ©ÇØÇÈ
	gravity->PutGravityOnActor(pos);


	// ïêäÌÇÃïœçX
	lpWeaponInventry.ChangeWeaponNum(gameCtl);

	// è∞Ç…Ç¢ÇÈèÍçá
	if (pos.y >= 500)
	{
		pos.y = 500;
	}

	// ±≤√—Ç∆ÇÃìñÇΩÇËîªíËÅAÇ±Ç±Ç©ÇÁ
	for (auto i = item.lock()->begin(); i != item.lock()->end(); i++)
	{
		// ãóó£åvéZ
		(*i)->CalcDistance(pos);
		isHit = (*i)->IsHit(size);
		if (isHit)
		{
			// ìñÇΩÇ¡ÇΩÇæÇØÇæÇ∆Ç‹Çæí«â¡Ã◊∏ﬁÇÕfalseÇÃÇ‹Ç‹
			(*i)->GetAddInventoryFlag() = false;
			if (!(*i)->GetisHadbyPlayer())
			{
				// â∫∑∞ÇâüÇ∑Ç∆èEÇ§”∞ºÆ›
				if (inputNow[0] && !inputOld[0])
				{
					myActionType = ANIM_PICKUP;
					if (inventory[registerNum]->GetWeaponType() == WEAPON_NONE)
					{
						// ïêäÌèÓïÒÇäiî[
						inventory[registerNum]->Add((*i)->GetWeaponType());
						// éÊìæÇµÇΩïêäÌÇ…≤›Õﬁ›ƒÿî‘çÜÇäÑÇËêUÇÈ
						(*i)->SetInventoryNum(registerNum);
						// 1Ç¬ïêäÌÇ™äiî[Ç≥ÇÍÇΩÇÁà íuÇÇ∏ÇÁÇ∑
						registerNum = (WeaponInventoryNum)(registerNum + 1);
						if (registerNum >= W_Num_4)
						{
							registerNum = W_Num_4;
						}

						// ïêäÌ±≤√—Ç™Ãﬂ⁄≤‘∞Ç©ÇÁéÊìæÇ≥ÇÍÇΩÃ◊∏ﬁÇtrueÇ…
						(*i)->GetisHadbyPlayer() = true;
						break;
					}
					else
					{
						// åªç›éwíËÇµÇƒÇ¢ÇÈïêäÌ≤›Õﬁ›ƒÿÇ™Ç∑Ç≈Ç…ñÑÇ‹Ç¡ÇƒÇ¢ÇΩÇÁ
						if (inventory[lpWeaponInventry.GetCurrentWeaponNum()]->GetWeaponType()
							!= WEAPON_NONE)
						{
							// åªç›éwíËÇµÇƒÇ¢ÇÈ≤›Õﬁ›ƒÿÇ…êVÇΩÇ…éÊìæÇµÇΩïêäÌ¿≤ÃﬂÇäiî[
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

	// ïêäÌÇéÃÇƒÇƒêVÇµÇ¢ïêäÌÇäiî[Ç∑ÇÈèàóù
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


	// ¿ﬁØº≠----------------------------------
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

	// ∂ﬁ∞ƒﬁ------------------------------
	if (inputNow[7])
	{
		// Œﬁ¿›ÇâüÇµÇƒÇ¢ÇÈä‘ÅA∂ﬁ∞ƒﬁÇ∑ÇÈ∂≥›ƒïœêîÇâ¡éZ
		guardTime++;
	}
	// Œﬁ¿›ÇâüÇµÇƒÇ¢Ç»Ç¢Ç∆∂≥›ƒïœêîÇÕ0Ç…ñﬂÇÈ
	else
	{
		guardTime = 0;
	}

	// ∂ﬁ∞ƒﬁÇµÇƒÇ¢ÇÈéûä‘Ç™0à»è„=Œﬁ¿›ÇâüÇµÇƒÇ¢ÇÈéûä‘ÇæÇØ∂ﬁ∞ƒﬁÇÇ∑ÇÈ
	if (guardTime > 0)
	{
		myActionType = ANIM_GUARD;
	}
	// Œﬁ¿›ÇâüÇµÇƒÇ¢Ç»Ç¢éûÇÕ∂ﬁ∞ƒﬁ∂≥›ƒïœêîÇÕ0Ç…ñﬂÇÈÇÃÇ≈waitÇ…ñﬂÇ∑
	/*else
	{
		myActionType = ANIM_WAIT;
	}*/
	// 1Ã⁄∞—ëOÇÃ⁄ÕﬁŸÇäiî[
	oldLevelCount = levelCount[myActionType][inventory[lpWeaponInventry.GetCurrentWeaponNum()]->GetWeaponType()];
	// çUåÇ±∆“∞ºÆ›Ç©ÇÁ(5/8ñÈãŒÇÃãxåeÇÃéû)
	if (inputNow[5] && !inputOld[5])
	{
		myActionType = ANIM_ATTACK;
		//çUåÇíiäKÇè„Ç∞ÇÈ
		levelCount[myActionType][inventory[lpWeaponInventry.GetCurrentWeaponNum()]->GetWeaponType()]++;
		attackFlag[inventory[lpWeaponInventry.GetCurrentWeaponNum()]->GetWeaponType()] = true;
	}

	// ñæì˙Ç±Ç±Ç©ÇÁ
	if (myActionType == ANIM_ATTACK)
	{
		if (levelCount[myActionType][inventory[lpWeaponInventry.GetCurrentWeaponNum()]->GetWeaponType()]
			 >= animLevel[myActionType][inventory[lpWeaponInventry.GetCurrentWeaponNum()]->GetWeaponType()])
		{
			levelCount[myActionType][inventory[lpWeaponInventry.GetCurrentWeaponNum()]->GetWeaponType()]
				= -1;
			myActionType = ANIM_WAIT;
		}
	}

	// åàíËŒﬁ¿›ÇâüÇ∑Ç∆ç°åªç›éwíËÇµÇƒÇ¢ÇÈïêäÌÇ…ïœçXÇ∑ÇÈÇ©åüì¢

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

	// é©ï™ÇÃactionTypeñàÇ…±∆“∞ºÆ›ÇïœçXÇµÇƒÇ¢Ç≠
	SetAnimation(lpImageMng.GetAnimString()[myActionType]);

	// ïêäÌ±≤∫›ÇÃŒﬂºﬁºÆ›ÇÃﬂ⁄≤‘∞Ç…í«è]
	lpWeaponInventry.UpDateInventoryPos(pos);
	//----------------------------------------

}

bool controlledPlayer::InitAnimation(WEAPON weapon)
{
	switch (weapon)
	{
	case WEAPON_SWORD:
		AddAnimation("attack", 9, 30, true, weapon);

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
	// ë“Çø”∞ºÆ›í«â¡
	AddAnimation("wait", 5, 9, true, weapon);
	// ¿ﬁØº≠”∞ºÆ›í«â¡
	AddAnimation("dash", 2, 10, false, weapon);
	// ∂ﬁ∞ƒﬁ”∞ºÆ›í«â¡
	AddAnimation("guard", 1, 10, true, weapon);
	// èEÇ¢”∞ºÆ›í«â¡
	AddAnimation("pickup", 5, 5, false, weapon);
	return true;
}
