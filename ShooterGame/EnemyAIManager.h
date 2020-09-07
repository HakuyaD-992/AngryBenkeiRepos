#pragma once
#include <list>
#include <vector>
#include <map>
#include <memory>
#include <functional>

#include "ActorType.h"

class ControlledPlayer;
class AIBase;
class Enemy;

class EnemyAIManager
{
public:
	EnemyAIManager(std::list<std::shared_ptr<Enemy>>& friends);
	~EnemyAIManager();

	// “G‚Ìs“®‚ÌŒˆ’è
	void UpDate(const std::shared_ptr<Enemy> enemy);

	//void SetAIFunc(const ActorType& type,const std::shared_ptr<AIBase>& aisystem);
private:
	// ©•ªˆÈŠO‚Ì–¡•û
	std::list<std::shared_ptr<Enemy>>& friendList_;


	std::map<ActorType,std::function<void(void)>> aiFunc_;

};

