#pragma once
#include <vector>
#include <string>
#include <array>
#include <map>

#include "Gravity.h"
#include "AddList.h"
#include "Vector2.h"
#include "ANIMATION.h"
#include "DIRECTION.h"
#include "WEAPON.h"
#include "GamePlay.h"
#include "WeaponInventry.h"
#include "Item_Weapon.h"
#include "Inventory.h"

// ��׸���̽�߰��
#define Speed 5
// �ޯ������̫�����
#define DashDefTime 20
// �U�����͂��󂯕t���鎞�ԁi���̎��Ԃ𒴂��Ă��܂��Ƒҋ@Ӱ��݂Ɏ����I�Ɉڍs�j
#define AttackLimTime 50

class GameController;

// ��Ұ��݂̎�ޕ�ð���
enum AnimationTable
{
	Animation_TB_Start,
	Animation_TB_Frame,
	Animation_TB_Interval,
	Animation_TB_Loop,
	AnimationTB_Max
};


class BasePlayer
{
public:
	BasePlayer();
	~BasePlayer();

	virtual void Draw(void);

	void UpDate(const GameController& gameCtl, WeakWeaponList item);
	// ��Ұ��ݒǉ��֐�
	bool AddAnimation(std::string animName, int frame, int interval, bool loop,WEAPON weapon);
	// ��Ұ��ݾ��
	bool SetAnimation(std::string animName);
	// ��Ұ��ݕ�����Ă̊֐�
	void SetAnimationString(std::string animString, const ANIMATION& anim);

	// ���ݱ�Ұ��݂̎擾
	std::string GetAnimation(void)
	{
		return animationName;
	}
	// ��ڲ԰���߼޼�ݎ擾�֐�
	const Vector2& GetPos(void)
	{
		return pos;
	}
	// �����擾�֐�
	const DIRECTION& GetDirection(void)
	{
		return direction;
	}

	// �����n
	bool Getdeleteflag(void)
	{
		return deleteFlag;
	}
	virtual void Delete(void)
	{
		deleteFlag = true;
	}

private:
	virtual void Action(const GameController& gameCtl,WeakWeaponList item) = 0;

	std::vector<std::string> fileName[ANIM_MAX];
	//��Ұ��݊֌W
	std::map<std::string, int[AnimationTB_Max]> animationTable[WEAPON_MAX];
	//�Đ������Ұ��ݖ�
	std::string animationName;

	// ���̏����׸�
	bool deleteFlag;

protected:
	// �߼޼��
	Vector2 pos;
	// �摜���ށi�����v��Ȃ��j
	Vector2 size;
	// ����
	DIRECTION direction;

	// �d�͊֌W
	Gravity* gravity;

	// �ެ��ߊ֌W-------------
	// �ެ��߂����
	float jumpForce;
	// �ެ��ߎ��̏����x
	float firstJumpSpeed;
	// �ެ��ߒ����׸�
	bool isJump;
	//------------------------

	// �ޯ���֌W--------------
	// �ޯ������
	int dashTime;
	// �ޯ�������׸�
	bool isDash;
	//------------------------

	// ����֌W-----------
	// ���������؂ɓo�^����ۂ̶��ĕϐ�
	WeaponInventoryNum registerNum;
	// �����Ă��镐��Ɠ��������׸�
	bool isHit;
	// ������E�����׸�
	bool isGet;
	// �s�v�ɂȂ���������̂Ă��׸�
	std::array<bool, W_Num_Max> throwAwayFlag;
	// ���������؂̏��i�[�p
	Inventory* inventory[W_Num_Max];

	// ���̎����̱�Ұ���
	ANIMATION myActionType;
	// �ǉ����镪�̱�Ұ��ݖ��̖��O
	std::string animName[ANIM_MAX];

	// �ް�ނ��Ă��鎞��
	int guardTime;
	// ���ݍU�������Ă����
	float attackCount;
	// �U���̘A�g������ۂ����݂̓��͂��󂯕t���鎞��
	// ���̎��ԍU�����݂���͂��Ă��Ȃ��Ƒҋ@Ӱ��݂Ɉڍs������
	int attackAllowTime;
	// ���했�ɍ����݂̍U���i�K���Ă���ϐ�
	std::array<int, WEAPON_MAX> attackLevelCount;
	// �U���i�K
	std::array<std::vector<int>,WEAPON_MAX> attackLevel;
	// ���했�̍ő�U����
	std::array<int, WEAPON_MAX> attackMaxNum;
	// ���݂̍U��Ӱ��݂��ڰі��Ɍ��������׸�
	std::array<bool, WEAPON_MAX> attackFlag;

	// ��Ұ��ݶ����
	unsigned int animationCount;
};
