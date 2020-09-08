#include <DxLib.h>
#include <algorithm>
#include "Spawner.h"
#include "ActorType.h"
#include "Enemy.h"
#include "Pod.h"
#include "Exoskeleton.h"
#include "AIBase.h"
#include "Floor.h"
#include "BulletBase.h"

Spawner::Spawner()
{
	Initialize();
}

Spawner::~Spawner()
{
}

void Spawner::MakeClone(std::list<std::shared_ptr<Enemy>>& enemies,
	std::vector<std::shared_ptr<ControlledPlayer>>& player,
	const Wave& wave)
{
	// ìGÇÃ¿≤Ãﬂ
	switch (wave)
	{
	case Wave::FirstWave:
		enemyType_ = ActorType::Spacenaut;

		break;
	case Wave::SecondWave:
		enemyType_ = ActorType::Pod + GetRand(static_cast<int>(ActorType::Exoskeleton));
		break;
	case Wave::ThirdWave:

		break;
	default:
		break;
	}
	// ÉXÉ|Å[ÉìŒﬂºﬁºÆ›
	auto spawnPos = Vector2I(10 + GetRand(floorX - 10),0);
	// zé≤ŒﬂºﬁºÆ›
	int z = -floorZ + GetRand(floorZ);

	enemyInstanceFunc_[enemyType](enemies,player, spawnPos, z,enemyType);
}

bool Spawner::Initialize(void)
{
	enemyInstanceFunc_.try_emplace(ActorType::Pod,
		[&](std::list<std::shared_ptr<Enemy>>& enemies,
			std::vector<std::shared_ptr<ControlledPlayer>>& player,
			Vector2I pos, int z, ActorType type) {

				enemies.emplace_back(std::make_shared<Pod>(pos, z, type, player));

		});
	enemyInstanceFunc_.try_emplace(ActorType::Exoskeleton,
		[&](std::list<std::shared_ptr<Enemy>>& enemies,
			std::vector<std::shared_ptr<ControlledPlayer>>& player,
			Vector2I pos, int z, ActorType type) {

				enemies.emplace_back(std::make_shared<Exoskeleton>(pos, z, type, player));
		});
	/*enemyInstanceFunc_.try_emplace(ActorType::Pod,
		[&](std::list<std::shared_ptr<Enemy>> enemies,
			std::shared_ptr<ControlledPlayer>& player,
			Vector2I pos, int z, ActorType type) {

				enemies.emplace_back(std::make_shared<Pod>(pos, z, type, player));
		});
	enemyInstanceFunc_.try_emplace(ActorType::Pod,
		[&](std::list<std::shared_ptr<Enemy>> enemies,
			std::shared_ptr<ControlledPlayer>& player,
			Vector2I pos, int z, ActorType type) {

				enemies.emplace_back(std::make_shared<Pod>(pos, z, type, player));
		});
	enemyInstanceFunc_.try_emplace(ActorType::Pod,
		[&](std::list<std::shared_ptr<Enemy>> enemies,
			std::shared_ptr<ControlledPlayer>& player,
			Vector2I pos, int z, ActorType type) {

				enemies.emplace_back(std::make_shared<Pod>(pos, z, type, player));
		});*/

	return true;
}
