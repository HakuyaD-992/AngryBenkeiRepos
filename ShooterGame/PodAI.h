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

	// ‰Šús“®
	bool Walk(std::list<std::shared_ptr<Enemy>>& enemies);
	// ÌßÚ²Ô°‚Æ‚ÌZ²‚ğ‡‚í‚¹‚é
	bool Z_Arrangement(std::list<std::shared_ptr<Enemy>>& enemies);
	// ÌßÚ²Ô°‚Æ‚ÌZ²‚ª‚ ‚Á‚½‚çUŒ‚
	bool Attack(std::list<std::shared_ptr<Enemy>>& enemies);
	// ÀŞÒ°¼Ş‚ğH‚ç‚Á‚½‚Æ‚«‚Ìs“®
	bool OnDamaged(std::list<std::shared_ptr<Enemy>>& enemies);
	// ÌßÚ²Ô°‚Æ‚ÌZ²‚ğ‚¸‚ç‚·(UŒ‚‰ñ”ğ)
	bool Evacuate(std::list<std::shared_ptr<Enemy>>& enemies);
	// ÌßÚ²Ô°‚Ì”wŒã‚É‰ñ‚è‚Ş
	bool Run(std::list<std::shared_ptr<Enemy>>& enemies);
	// €‚Ê
	bool Death(std::list<std::shared_ptr<Enemy>>& enemies);

private:

	void Initialize(void);
	bool(PodAI::* updater_)(std::list<std::shared_ptr<Enemy>>&);

};

