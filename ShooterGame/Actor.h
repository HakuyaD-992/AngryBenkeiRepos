#pragma once
#include <string>
#include <map>
#include "Geometory.h"
#include "ActorType.h"
#include "Gravity.h"
#include "CollisionManager.h"

class Actor
{
public:
	Actor();
	~Actor();

	virtual void UpDate(void) = 0;
	virtual bool Initialize(void);
	// (�{����Initialize�ɏ����Ă��悩�������AInitialize���c��ɂȂ��Ă��܂����ߊO�ɓ�������)
	virtual void RectInitializer(void);
	virtual void Draw(void);
	virtual void Draw_(void) = 0;
	virtual void UpDateAnimation(const std::string& animName);
	// ��Ұ��݂̕ύX
	void ChangeAnimation(std::string animName);

	const std::string& GetCurrentAnimation(void);

	virtual bool OnFloor(void);

	// ���ߎ擾�֐�
	virtual const ActorType& GetType(void)
	{
		return type_;
	}

	int& GetHpNum(void)
	{
		return hpNum_;
	}

	// �߼޼�ݎ擾
	Vector2I& GetPos(void)
	{
		return pos_;
	}
	// ���ގ擾
	const Vector2I& GetSize(void)
	{
		return size_;
	}
	// Z�߼޼�ݎ擾
	int& GetZPos(void)
	{
		return z_;
	}
	bool& GetisTurnFlag(void)
	{
		return isTurnLeft_;
	}
	Vector2I& GetSpeed(void)
	{
		return speed_;
	}
	int& GetZSpeed(void)
	{
		return zSpeed_;
	}

	bool& GetisAnimEnd(void)
	{
		return isAnimEnd_;
	}

	virtual void Delete(void)
	{
		deleteFlag_ = true;
	}

	virtual const bool& GetDeleteFlag(void)
	{
		return deleteFlag_;
	}

	virtual int& GetHp(void)
	{
		return hp_[hpNum_ - 1];
	}

	float& GetAlpha(void)
	{
		return alpha_percent;
	}

	bool& IsJumping(void)
	{
		return isJump_;
	}

	virtual bool& GetOnDamaged(void)
	{
		return onDamaged_;
	}

	virtual const int& GetMaxHp(void)
	{
		return maxHp_;
	}

private:
	Vector2I drawPos_;

	float count_;
protected:
	bool deleteFlag_;
	Vector2I pos_;
	// ��߰��
	Vector2I speed_;
	// �����̻���
	Vector2I size_;
	Vector2I hpPos_;

	std::string name_;
	// ���䂫�̽�߰��
	int zSpeed_;
	int z_;

	Vector2I shadowRadius_;
	// �ެ��߽�߰��
	int jumpSpeed_;
	float jumpFirstSpeed_;
	float jumpForce_;
	// ��Ұ�ނ�H������׸�
	bool onDamaged_;
	// �ެ����׸�
	bool isJump_;
	int drawHpCnt_;
	bool isDrawHp_;

	// �d��
	Gravity* gravity_;
	// ����������
	ActorType type_;

	// �e��ڲ԰�A�G�̋�`���
	AnimationRect rect_;

	// �p������
	float duration_;
	// ��Ұ��݂��I�������׸�
	bool isAnimEnd_;
	// �U�����Ă��邩���׸�
	bool isAttack_;
	// ��Ұ��݂̍ۂ̱�Ұ��ݖ��Ʊ�Ұ����ڰѐ�
	std::map<std::string, int> animationSet_;
	std::string currentAnimation_;
	// ��Ұ��݂̍ۂ̶�����ϐ�
	float animationCount_;
	// ��Ұ��݂�ٰ�߂���̂����׸�
	std::map<std::string, bool> isLoop_;

	// �����̌����Ă�������׸�
	bool isTurnLeft_;
	// �����������Ă����׸�
	bool isMove_;
	// �g�嗦
	double exRate_;
	// ��]��
	double rotRate_;

	// �e������HP
	std::vector<int> hp_;
	// hp�̖{��
	int hpNum_;
	// hp�̍ő�l
	int maxHp_;
	// ���ߗ�
	float alpha_percent;
};

