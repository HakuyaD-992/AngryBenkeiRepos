#pragma once
#include <string>
#include "Geometory.h"
#include "ObjectType.h"

class Object
{
public:
	Object();
	~Object();
	// �`��
	virtual void Draw(void);
	// �߼޼�ݾ��
	void SetPos(const Vector2I& pos);
	// ������
	bool Initialize(void);
	// �߼޼�ݎ擾
	const Vector2I& GetPos(void)
	{
		return pos_;
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
};

