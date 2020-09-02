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

	// ‰Šús“®
	void Walk(void);
	// ÌßÚ²Ô°‚Æ‚ÌZ²‚ğ‡‚í‚¹‚é
	void Z_Arrangement(void);
	// ÌßÚ²Ô°‚Æ‚ÌZ²‚ª‚ ‚Á‚½‚çUŒ‚
	void Attack(void);
	// ÌßÚ²Ô°‚Æ‚ÌZ²‚ğ‚¸‚ç‚·(UŒ‚‰ñ”ğ)
	void Evacuate(void);


};

