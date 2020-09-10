#include <DxLib.h>
#include <algorithm>
#include "Spawner.h"
#include "PlayScene.h"
#include "ActorType.h"
#include "Enemy.h"
#include "Pod.h"
#include "Exoskeleton.h"
#include "Spacenaut.h"
#include "Bigboy.h"
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
	// 敵のﾀｲﾌﾟ
	switch (wave)
	{
	case Wave::FirstWave:
		enemyType_ = ActorType::Pod;
		// スポーンﾎﾟｼﾞｼｮﾝ
		spawnPos_ = Vector2I(10 + GetRand(floorX - 10), 0);
		// z軸ﾎﾟｼﾞｼｮﾝ
		spawnPosZ_ = -floorZ + GetRand(floorZ);
		//// スポーンﾎﾟｼﾞｼｮﾝ
		//spawnPos_ = Vector2I(floorX - 100, 0);
		//// z軸ﾎﾟｼﾞｼｮﾝ
		//spawnPosZ_ = -floorZ + 80;
		break;
	case Wave::SecondWave:
		enemyType_ = ActorType::Pod + GetRand(static_cast<int>(ActorType::Pod));
		// スポーンﾎﾟｼﾞｼｮﾝ
		spawnPos_ = Vector2I(10 + GetRand(floorX - 10), 0);
		// z軸ﾎﾟｼﾞｼｮﾝ
		spawnPosZ_ = -floorZ + GetRand(floorZ);
		break;
	case Wave::ThirdWave:
		if (bossFlag_)
		{
			enemyType_ = ActorType::Bigboy;
			// スポーンﾎﾟｼﾞｼｮﾝ
			spawnPos_ = Vector2I(floorX - 100, 0);
			// z軸ﾎﾟｼﾞｼｮﾝ
			spawnPosZ_ = -floorZ + 80;
			bossFlag_ = false;
		}
		else
		{
			enemyType_ = ActorType::Pod + GetRand(static_cast<int>(ActorType::Pod));
			// スポーンﾎﾟｼﾞｼｮﾝ
			spawnPos_ = Vector2I(10 + GetRand(floorX - 10), 0);
			// z軸ﾎﾟｼﾞｼｮﾝ
			spawnPosZ_ = -floorZ + GetRand(floorZ);
		}
		break;
	default:
		break;
	}

	enemyInstanceFunc_[enemyType_](enemies,player, spawnPos_, spawnPosZ_,enemyType_);
}

bool Spawner::Initialize(void)
{
	bossFlag_ = true;
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
	enemyInstanceFunc_.try_emplace(ActorType::Bigboy,
		[&](std::list<std::shared_ptr<Enemy>>& enemies,
			std::vector<std::shared_ptr<ControlledPlayer>>& player,
			Vector2I pos, int z, ActorType type) {

				enemies.emplace_back(std::make_shared<Bigboy>(pos, z, type, player));
		});
	enemyInstanceFunc_.try_emplace(ActorType::Spacenaut,
		[&](std::list<std::shared_ptr<Enemy>>& enemies,
			std::vector<std::shared_ptr<ControlledPlayer>>& player,
			Vector2I pos, int z, ActorType type) {
				enemies.emplace_back(std::make_shared<Spacenaut>(pos, z, type, player));
		});
	/*enemyInstanceFunc_.try_emplace(ActorType::Pod,
		[&](std::list<std::shared_ptr<Enemy>>& enemies,
			std::vector<std::shared_ptr<ControlledPlayer>>& player,
			Vector2I pos, int z, ActorType type) {

				enemies.emplace_back(std::make_shared<Pod>(pos, z, type, player));
		});
	enemyInstanceFunc_.try_emplace(ActorType::Pod,
		[&](std::list<std::shared_ptr<Enemy>>& enemies,
			std::vector<std::shared_ptr<ControlledPlayer>>& player,
			Vector2I pos, int z, ActorType type) {

				enemies.emplace_back(std::make_shared<Pod>(pos, z, type, player));
		});*/

	return true;
}
