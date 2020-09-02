#include <DxLib.h>
#include <algorithm>
#include "Spawner.h"
#include "ActorType.h"
#include "Enemy.h"
#include "Pod.h"
#include "Exoskeleton.h"

Spawner::Spawner()
{
	Initialize();
}

Spawner::~Spawner()
{
}

void Spawner::MakeClone(std::list<std::shared_ptr<Enemy>>& enemies,
	std::list<std::shared_ptr<ControlledPlayer>>& player)
{
	// ìGÇÃ¿≤Ãﬂ
	auto enemyType = ActorType::Pod + GetRand(static_cast<int>(ActorType::Pod));
	// ÉXÉ|Å[ÉìŒﬂºﬁºÆ›
	auto spawnPos = Vector2I(10 + GetRand(800 - 10), -30);
	// zé≤ŒﬂºﬁºÆ›
	int z = -100 + GetRand(200);

	enemyInstanceFunc_[enemyType](enemies,player, spawnPos, z,enemyType);
}

bool Spawner::Initialize(void)
{
	enemyInstanceFunc_.try_emplace(ActorType::Pod,
		[&](std::list<std::shared_ptr<Enemy>>& enemies,
			std::list<std::shared_ptr<ControlledPlayer>>& player,
			Vector2I pos,int z,ActorType type) {

				enemies.emplace_back(std::make_shared<Pod>(pos, z, type, player));
		});
	enemyInstanceFunc_.try_emplace(ActorType::Exoskeleton,
		[&](std::list<std::shared_ptr<Enemy>>& enemies,
			std::list<std::shared_ptr<ControlledPlayer>>& player,
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
