#pragma once
#include <memory>
#include <list>
#include <map>
#include <functional>
#include "Geometory.h"

#include "ActorType.h"

class Enemy;
class ControlledPlayer;

class Spawner
{
public:
	Spawner();
	~Spawner();

	void MakeClone(std::list<std::shared_ptr<Enemy>>& enemies,
		std::list<std::shared_ptr<ControlledPlayer>>& player);

private:
	bool Initialize(void);

	std::map<ActorType,std::function<void(std::list<std::shared_ptr<Enemy>>&,
		std::list<std::shared_ptr<ControlledPlayer>>&,
		Vector2I pos, int z, ActorType type)>> enemyInstanceFunc_;
};

