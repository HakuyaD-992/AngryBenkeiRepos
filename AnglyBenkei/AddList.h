#pragma once
#include <list>
#include <memory>

class BasePlayer;
class EnemyBase;
class ItemBase;

using namespace std;

// ¹Ş°Ñ“oê·¬×¸À°—p‚ÌØ½Äì¬
using SharedPtr = shared_ptr<BasePlayer>;
using SharedList = list<SharedPtr>;
using SharedListPtr = shared_ptr<SharedList>;

using WeakList = weak_ptr<SharedList>;
using SharedListItr = SharedList::iterator;

// ¹Ş°Ñ“oê·¬×¸À°—p‚ÌØ½Äì¬(G‹›)
using SharedEnemyPtr = shared_ptr<EnemyBase>;
using SharedEnemyList = list<SharedEnemyPtr>;
using SharedEnemyListPtr = shared_ptr<SharedEnemyList>;

using WeakEnemyList = weak_ptr<SharedEnemyList>;
using SharedEnemyListItr = SharedEnemyList::iterator;

// •Ší±²ÃÑ—p‚ÌØ½Äì¬
using SharedWeaponPtr = shared_ptr<ItemBase>;
using SharedWeaponList = list<SharedWeaponPtr>;
using SharedWeaponListPtr = shared_ptr<SharedWeaponList>;

using WeakWeaponList = weak_ptr<SharedWeaponList>;
using SharedWeaponListItr = SharedWeaponList::iterator;

// •Ší±²ÃÑ—p(²İÍŞİÄØ)‚ÌØ½Äì¬
using SharedWeaponInventoryPtr = shared_ptr<ItemBase>;
using SharedWeaponInventoryList = list<SharedWeaponInventoryPtr>;
using SharedWeaponInventoryListPtr = shared_ptr<SharedWeaponInventoryList>;

using WeakWeaponInventoryList = weak_ptr<SharedWeaponInventoryList>;
using SharedWeaponInventoryListItr = SharedWeaponInventoryList::iterator;

// Ø½Ä‚Ö‚Ì’Ç‰Á
struct AddList
{
	SharedListItr operator()(WeakList w, SharedPtr ptr)
	{
		w.lock()->push_back(ptr);

		SharedListItr itr = w.lock()->end();

		itr--;

		return itr;
	}
};

// G‹›‚ÌØ½Ä‚Ö‚Ì’Ç‰Á
struct AddEnemyList
{
	SharedEnemyListItr operator()(WeakEnemyList w, SharedEnemyPtr ptr)
	{
		w.lock()->push_back(ptr);

		SharedEnemyListItr itr = w.lock()->end();

		itr--;

		return itr;
	}
};


// Ø½Ä‚Ö‚Ì’Ç‰Á
struct AddWeaponList
{
	SharedWeaponListItr operator()(WeakWeaponList w, SharedWeaponPtr ptr)
	{
		w.lock()->push_back(ptr);

		SharedWeaponListItr itr = w.lock()->end();

		itr--;

		return itr;
	}
};

// Ø½Ä‚Ö‚Ì’Ç‰Á
struct AddWeaponInventory
{
	SharedWeaponInventoryListItr operator()(WeakWeaponInventoryList w, SharedWeaponInventoryPtr ptr)
	{
		w.lock()->push_back(ptr);

		SharedWeaponInventoryListItr itr = w.lock()->end();

		itr--;

		return itr;
	}
};