#pragma once
#include <memory>
#include <list>


class BasePlayer;
class BaseEnemy;

using namespace std;

// create player list
using SharedPlayerPtr = shared_ptr<BasePlayer>;
using SharedPlayerList = list<SharedPlayerPtr>;
using SharedPlayerListPtr = shared_ptr<SharedPlayerList>;

using WeakPlayerList = weak_ptr<SharedPlayerList>;
using SharedPlayerListItr = SharedPlayerList::iterator;

// create enemy list
using SharedEnemyPtr = shared_ptr<BaseEnemy>;
using SharedEnemyList = list<SharedEnemyPtr>;
using SharedEnemyListPtr = shared_ptr<SharedEnemyList>;

using WeakEnemyList = weak_ptr<SharedEnemyList>;
using SharedEnemyListItr = SharedEnemyList::iterator;

struct AddPlayerList
{
	SharedPlayerListItr operator()(WeakPlayerList playerList, SharedPlayerPtr playerPtr)
	{
		playerList.lock()->push_back(playerPtr);
		SharedPlayerListItr playerItr = playerList.lock()->end();;
		playerItr--;

		return playerItr;
	}
};

struct AddEnemyList
{
	SharedEnemyListItr operator()(WeakEnemyList enemyList, SharedEnemyPtr enemyPtr)
	{
		enemyList.lock()->push_back(enemyPtr);
		SharedEnemyListItr enemyItr = enemyList.lock()->end();;
		enemyItr--;

		return enemyItr;
	}
};
