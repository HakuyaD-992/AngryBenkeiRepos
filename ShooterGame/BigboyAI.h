#pragma once
#include "AIBase.h"
class BigboyAI :
	public AIBase
{
public:
	BigboyAI(Enemy& enemy);
	~BigboyAI();

	void Update(std::list<std::shared_ptr<Enemy>>& enemies);
private:
	void Initialize(void);
	// ä÷êîŒﬂ≤›¿
	void(BigboyAI::* updater)(std::list<std::shared_ptr<Enemy>>& enemies);

};

