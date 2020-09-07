#pragma once
#include "Enemy.h"


class Exoskeleton :
	public Enemy
{
public:
	Exoskeleton(Vector2I pos,int z,ActorType type,
		std::vector<std::shared_ptr<ControlledPlayer>>& player);
	~Exoskeleton();

	void UpDate(void);
	void Draw_(void);

	void (Exoskeleton::* updater)(void);

private:
	// ����
	void Run(void);
	// ��ڲ԰��Z���Ɏ�����Z�������킹��
	void ArrangementZ(void);
	// Z������ڲ԰�Ƃ�������U��������(�e���o��)
	void Attack(void);
	// �e�������Ȃ�Έ�U�ޔ�
	void Evacuation(void);
	// �e�̕�[
	void RefillBullet(void);
};
