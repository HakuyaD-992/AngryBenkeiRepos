#pragma once
#include <memory>
#include <list>


class BasePlayer;

using namespace std;

// create player list
using SharedPlayerPtr = shared_ptr<BasePlayer>;
using SharedPlayerList = list<SharedPlayerPtr>;
using SharedPlayerListPtr = shared_ptr<SharedPlayerList>;

using WeakPlayerList = weak_ptr<SharedPlayerList>;
using SharedPlayerListItr = SharedPlayerList::iterator;

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
