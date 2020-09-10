#pragma once
#include <memory>
#include <list>
#include <vector>
#include <map>
#include <functional>
#include "Geometory.h"
#include "Wave.h"

#include "ActorType.h"

class Enemy;
class EnemyAIManager;
class BulletBase;
class AIBase;
class ControlledPlayer;

class Spawner
{
public:
	Spawner();
	~Spawner();

	void MakeClone(std::list<std::shared_ptr<Enemy>>& enemies,
		std::vector<std::shared_ptr<ControlledPlayer>>& player,
		const Wave& wave, const bool& flg = false);

	const bool& GetBossCreateFlag(void)
	{
		return bossFlag_;
	}

private:
	bool Initialize(void);

	std::map<ActorType,std::function<void(std::list<std::shared_ptr<Enemy>>&,
		std::vector<std::shared_ptr<ControlledPlayer>>&,
		Vector2I pos, int z, ActorType type)>> enemyInstanceFunc_;

	ActorType enemyType_;
	Vector2I spawnPos_;
	int spawnPosZ_;
	bool bossFlag_;
};

