#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Geometory.h"
#include "ObjectType.h"

class ControlledPlayer;

class Object
{
public:
	Object(std::shared_ptr<ControlledPlayer>& player);
	~Object();
	// �`��
	virtual void Draw(void) = 0;

	// �߼޼�ݾ��
	void SetPos(const Vector2I& pos);
	// ������
	virtual bool Initialize(void);
	// �߼޼�ݎ擾
	const Vector2I& GetPos(void)
	{
		return pos_;
	}

	const ObjectType& GetType(void) const
	{
		return type_;
	}

private:

protected:
	// �߼޼��
	Vector2I pos_;
	// �g�嗦
	double exRate_;
	// ��]��
	double rotRate_;
	// ��޼ު�Ă�����
	ObjectType type_;
	// �摜�����
	int imageHandle_;
	// ���g�̵�޼ު��Ȱ�
	std::string name_;

	std::shared_ptr<ControlledPlayer>& player_;
};

