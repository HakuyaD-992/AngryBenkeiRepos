#pragma once
#include <memory>
#include "AIBase.h"

class Enemy;

class PodAI :
	public AIBase
{
public:
	PodAI(Enemy& enemy);
	~PodAI();

	void Update(std::list<std::shared_ptr<Enemy>>& enemies);

	// �����s��
	bool Walk(std::list<std::shared_ptr<Enemy>>& enemies);
	// ��ڲ԰�Ƃ�Z�������킹��
	bool Z_Arrangement(std::list<std::shared_ptr<Enemy>>& enemies);
	// ��ڲ԰�Ƃ�Z������������U��
	bool Attack(std::list<std::shared_ptr<Enemy>>& enemies);
	// ��Ұ�ނ�H������Ƃ��̍s��
	bool OnDamaged(std::list<std::shared_ptr<Enemy>>& enemies);
	// ��ڲ԰�Ƃ�Z�������炷(�U�����)
	bool Evacuate(std::list<std::shared_ptr<Enemy>>& enemies);

	bool Run(std::list<std::shared_ptr<Enemy>>& enemies);

private:

	void Initialize(void);
	bool(PodAI::* updater_)(std::list<std::shared_ptr<Enemy>>&);

};
