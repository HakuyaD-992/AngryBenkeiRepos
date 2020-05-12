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

	// ���������؂̕`��
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

	// �d�͂�������
	gravity->PutGravityOnActor(pos);


	// ����̕ύX
	lpWeaponInventry.ChangeWeaponNum(gameCtl);

	// ���ɂ���ꍇ
	if (pos.y >= 500)
	{
		pos.y = 500;
	}

	// ���тƂ̓����蔻��A��������
	for (auto i = item.lock()->begin(); i != item.lock()->end(); i++)
	{
		// �����v�Z
		(*i)->CalcDistance(pos);
		isHit = (*i)->IsHit(size);
		if (isHit)
		{
			// ���������������Ƃ܂��ǉ��׸ނ�false�̂܂�
			(*i)->GetAddInventoryFlag() = false;
			if (!(*i)->GetisHadbyPlayer())
			{
				// �����������ƏE��Ӱ���
				if (inputNow[0] && !inputOld[0])
				{
					myActionType = ANIM_PICKUP;
					if (inventory[registerNum]->GetWeaponType() == WEAPON_NONE)
					{
						// ��������i�[
						inventory[registerNum]->Add((*i)->GetWeaponType());
						// �擾��������ɲ�����ؔԍ�������U��
						(*i)->SetInventoryNum(registerNum);
						// 1���킪�i�[���ꂽ��ʒu�����炷
						registerNum = (WeaponInventoryNum)(registerNum + 1);
						if (registerNum >= W_Num_4)
						{
							registerNum = W_Num_4;
						}

						// �����т���ڲ԰����擾���ꂽ�׸ނ�true��
						(*i)->GetisHadbyPlayer() = true;
						break;
					}
					else
					{
						// ���ݎw�肵�Ă��镐�������؂����łɖ��܂��Ă�����
						if (inventory[lpWeaponInventry.GetCurrentWeaponNum()]->GetWeaponType()
							!= WEAPON_NONE)
						{
							// ���ݎw�肵�Ă��������؂ɐV���Ɏ擾�����������߂��i�[
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

	// ������̂ĂĐV����������i�[���鏈��
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


	// �ޯ��----------------------------------
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

	// �ް��------------------------------
	if (inputNow[7])
	{
		// ���݂������Ă���ԁA�ް�ނ��鶳�ĕϐ������Z
		guardTime++;
	}
	// ���݂������Ă��Ȃ��ƶ��ĕϐ���0�ɖ߂�
	else
	{
		guardTime = 0;
	}

	// �ް�ނ��Ă��鎞�Ԃ�0�ȏ�=���݂������Ă��鎞�Ԃ����ް�ނ�����
	if (guardTime > 0)
	{
		myActionType = ANIM_GUARD;
	}
	// ���݂������Ă��Ȃ����Ͷް�޶��ĕϐ���0�ɖ߂�̂�wait�ɖ߂�
	/*else
	{
		myActionType = ANIM_WAIT;
	}*/
	// 1�ڰёO�����ق��i�[
	oldLevelCount = levelCount[myActionType][inventory[lpWeaponInventry.GetCurrentWeaponNum()]->GetWeaponType()];
	// �U����Ұ��݂���(5/8��΂̋x�e�̎�)
	if (inputNow[5] && !inputOld[5])
	{
		myActionType = ANIM_ATTACK;
		//�U���i�K���グ��
		levelCount[myActionType][inventory[lpWeaponInventry.GetCurrentWeaponNum()]->GetWeaponType()]++;
		attackFlag[inventory[lpWeaponInventry.GetCurrentWeaponNum()]->GetWeaponType()] = true;
	}

	// ������������
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

	// �������݂������ƍ����ݎw�肵�Ă��镐��ɕύX���邩����

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

	// ������actionType���ɱ�Ұ��݂�ύX���Ă���
	SetAnimation(lpImageMng.GetAnimString()[myActionType]);

	// �����݂��߼޼�݂���ڲ԰�ɒǏ]
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
	// �҂�Ӱ��ݒǉ�
	AddAnimation("wait", 5, 9, true, weapon);
	// �ޯ��Ӱ��ݒǉ�
	AddAnimation("dash", 2, 10, false, weapon);
	// �ް��Ӱ��ݒǉ�
	AddAnimation("guard", 1, 10, true, weapon);
	// �E��Ӱ��ݒǉ�
	AddAnimation("pickup", 5, 5, false, weapon);
	return true;
}
