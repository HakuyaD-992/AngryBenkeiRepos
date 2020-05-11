#pragma once
#include <string>


#include "Gravity.h"
#include "AddList.h"
#include "Vector2.h"
#include "ImageManager.h"
#include "WEAPON.h"
#include "DIRECTION.h"
#include "WeaponInventry.h"

class ItemBase
{
public:
	ItemBase();
	~ItemBase();
	virtual void UpDate(WeakList charaList);

	// ����`��
	virtual void Draw(void);
	// ����̏������֘A
	bool Init(std::string imgName,Vector2 size);
	// ���т̓����֐�
	// �G�����񂾂��߮�݂Əo�Ă���悤��
	virtual void Move(WeakList charaList) = 0;
	// ���т���ڲ԰�Ƃ̋����v�Z�֐�
	void CalcDistance(const Vector2& pos);
	// ���т���ڲ԰�̓����蔻��֐�
	virtual bool IsHit(const Vector2& size);

	// �����̕������ߎ擾�֐�
	virtual WEAPON& GetWeaponType(void)
	{
		return weaponType;
	}

	// ���g����ڲ԰����擾���ꂽ�����׸ގ擾�֐�
	virtual bool& GetisHadbyPlayer(void)
	{
		return isHadbyPlayer;
	}

	// ���g���̂Ă�ꂽ�׸ނ̎擾�֐�
	virtual bool& GetisThrowAway(void)
	{
		return isThrowAway;
	}
	// ������ؔԍ����
	void SetInventoryNum(const WeaponInventoryNum& wNum);

	// �����яo���̓����֐�
	virtual void JumpFromPlayer(void);

	// ���������؂Ɋi�[����Ă��镐�킾�Ƃ��̊i�[����Ă��������ؔԍ���Ԃ�
	WeaponInventoryNum& GetInventoryNum(void)
	{
		return myInventoryNum;
	}
	// ������ؒǉ��׸ގ擾�֐�
	bool& GetAddInventoryFlag(void)
	{
		return addInventoryFlag;
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
	// ����̉摜��
	std::string imageName;
	// �����׸�
	bool deleteFlag;

protected:
	// �߼޼��
	Vector2 pos;
	// ����
	Vector2 size;
	// ���킪��ڲ԰�����яo������
	DIRECTION jumpDir;
	// ��������
	WEAPON weaponType;
	// ����
	Vector2 distance;
	// �d��
	Gravity* gravity;
	// ���g����ڲ԰����擾���ꂽ�����׸�
	bool isHadbyPlayer;
	// ���g�������؂ɒǉ����邩���׸�
	bool addInventoryFlag;
	// ���ɏ����ς݂̊i�[����Ă��镐�������ؔԍ���\��
	WeaponInventoryNum myInventoryNum;
	// ��ڲ԰����̂Ă�ꂽ�׸�
	bool isThrowAway;
	// �̂Ă�ꂽ���ɱ��т��߮�݂Ɣ���׸�
	bool isThrowMove;

	// �߮�݂Ɣ�яo�������x
	float startingJumpSpeed;
	// ��яo����
	float jumpForce;
	
};

