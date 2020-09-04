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

	virtual bool OnFloor(void);
	virtual bool InFloor(void);

	// �߼޼�ݎ擾
	const Vector2I& GetPos(void) const
	{
		return pos_;
	}
	// Z�߼޼�ݎ擾
	const int& GetZPos(void) const
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
private:
	Vector2I drawPos_;
	float count_;
protected:
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

	// �e������HP��
	float hp_;

	// �����̌����Ă�������׸�
	bool isTurnLeft_;
	// �����������Ă����׸�
	bool isMove_;
	// �g�嗦
	double exRate_;
	// ��]��
	double rotRate_;
};

