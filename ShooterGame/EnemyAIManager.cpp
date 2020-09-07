#include "EnemyAIManager.h"
#include "Enemy.h"
#include "PodAI.h"

EnemyAIManager::EnemyAIManager(std::list<std::shared_ptr<Enemy>>& friends):
friendList_(friends)
{

}

EnemyAIManager::~EnemyAIManager()
{

}

void EnemyAIManager::UpDate(const std::shared_ptr<Enemy> enemy)
{
	enemy->GetAISystem()->AIAction(friendList_);
}


