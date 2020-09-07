#pragma once
#include <list>
#include <memory>

class Enemy;
class AICollider;

class AIBase
{
public:
	AIBase(Enemy& enemy);
	~AIBase();

	virtual void AIAction(std::list<std::shared_ptr<Enemy>>& enemies);

	virtual void Update(std::list<std::shared_ptr<Enemy>>& enemies) = 0;
	virtual void Initialize(void) = 0;
	// Šeº×²ÀŞ°‚Ì“–‚½‚è”»’è(©•ª©g‚Æ©•ªˆÈŠO‚Ì–¡•û‚Å”äŠr)
	bool IsHitFriends(std::list<std::shared_ptr<Enemy>>& enemies);
private:


protected:
	// ©•ª©g
	Enemy& me_;
	// 1‰ñe’e‚ğ²İ½Àİ½‚µ‚½‚çtrue‚É
	bool createBulletFlag_;
};

