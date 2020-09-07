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
	virtual bool InFloor(void);

	// ���ߎ擾�֐�
	virtual const ActorType& GetType(void)
	{
		return type_;
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
	const Vector2I& GetSpeed(void) const
	{
		return speed_;
	}
	const int& GetZSpeed(void) const
	{
		return zSpeed_;
	}
	const bool& GetisTurnFlag(void)
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
	// ���䂫�̽�߰��
	int zSpeed_;
	int z_;
	// �ެ��߽�߰��
	int jumpSpeed_;
	float jumpFirstSpeed_;
	float jumpForce_;
	// �ެ����׸�
	bool isJump_;

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
	// �G����̍U���H�炢����
	bool isDamaged_;

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
	int hp_;
};
