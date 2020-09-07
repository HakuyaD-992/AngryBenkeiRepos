#pragma once
#include "AIBase.h"
class ExoskeletonAI :
    public AIBase
{
public:
	ExoskeletonAI(Enemy& enemy);
	~ExoskeletonAI();

	void Update(std::list<std::shared_ptr<Enemy>>& enemies);

	// ��ڲ԰�̔w��ɉ�荞��
	bool Run(std::list<std::shared_ptr<Enemy>>& enemies);
	// ����
	bool Death(std::list<std::shared_ptr<Enemy>>& enemies);
private:

	void Initialize(void);
	bool(ExoskeletonAI::* updater_)(std::list<std::shared_ptr<Enemy>>&);

	int frame;
	float rad;	//���W�A���p�x
};

