#pragma once
#include "AIBase.h"
class ExoskeletonAI :
    public AIBase
{
public:
	ExoskeletonAI(Enemy& enemy);
	~ExoskeletonAI();

	void Update(std::list<std::shared_ptr<Enemy>>& enemies);

	// ÌßÚ²Ô°‚Ì”wŒã‚É‰ñ‚è‚Ş
	bool Run(std::list<std::shared_ptr<Enemy>>& enemies);
	// €‚Ê
	bool Death(std::list<std::shared_ptr<Enemy>>& enemies);
private:

	void Initialize(void);
	bool(ExoskeletonAI::* updater_)(std::list<std::shared_ptr<Enemy>>&);

	int frame;
	float rad;	//ƒ‰ƒWƒAƒ“Šp“x
};

