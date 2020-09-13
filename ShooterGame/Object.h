#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Geometory.h"
#include "ObjectType.h"

class ControlledPlayer;
<<<<<<< HEAD

class Object
{
public:
	Object(std::shared_ptr<ControlledPlayer>& player);
=======
class Object
{
public:
	Object(std::vector<std::shared_ptr<ControlledPlayer>>& player_);
>>>>>>> 56ac109e597b0e82e8d13a0ad1b670f3c322930f
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

<<<<<<< HEAD
	std::shared_ptr<ControlledPlayer>& player_;
=======
	std::vector<std::shared_ptr<ControlledPlayer>>& player_;
>>>>>>> 56ac109e597b0e82e8d13a0ad1b670f3c322930f
};

