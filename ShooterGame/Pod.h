#pragma once
#include "Enemy.h"
class Pod :
	public Enemy
{
public:
	Pod(Vector2I pos, int z,ActorType type,
		std::list<std::shared_ptr<ControlledPlayer>>& player);
	~Pod();

	void UpDate(void);
	void Draw_(void);

	void(Pod::* updater_)(void);

private:

	// �����s��
	void Walk(void);
	// ��ڲ԰�Ƃ�Z�������킹��
	void Z_Arrangement(void);
	// ��ڲ԰�Ƃ�Z������������U��
	void Attack(void);
	// ��ڲ԰�Ƃ�Z�������炷(�U�����)
	void Evacuate(void);


};

