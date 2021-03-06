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

	// 敵の行動の決定
	void UpDate(const std::shared_ptr<Enemy> enemy);

	//void SetAIFunc(const ActorType& type,const std::shared_ptr<AIBase>& aisystem);
private:
	// 自分以外の味方
	std::list<std::shared_ptr<Enemy>>& friendList_;


	std::map<ActorType,std::function<void(void)>> aiFunc_;

};

