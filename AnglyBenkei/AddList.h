#pragma once
#include <list>
#include <memory>

class BasePlayer;
class EnemyBase;
class ItemBase;

using namespace std;

// �ްѓo�귬׸���p��ؽč쐬
using SharedPtr = shared_ptr<BasePlayer>;
using SharedList = list<SharedPtr>;
using SharedListPtr = shared_ptr<SharedList>;

using WeakList = weak_ptr<SharedList>;
using SharedListItr = SharedList::iterator;

// �ްѓo�귬׸���p��ؽč쐬(�G��)
using SharedEnemyPtr = shared_ptr<EnemyBase>;
using SharedEnemyList = list<SharedEnemyPtr>;
using SharedEnemyListPtr = shared_ptr<SharedEnemyList>;

using WeakEnemyList = weak_ptr<SharedEnemyList>;
using SharedEnemyListItr = SharedEnemyList::iterator;

// �����їp��ؽč쐬
using SharedWeaponPtr = shared_ptr<ItemBase>;
using SharedWeaponList = list<SharedWeaponPtr>;
using SharedWeaponListPtr = shared_ptr<SharedWeaponList>;

using WeakWeaponList = weak_ptr<SharedWeaponList>;
using SharedWeaponListItr = SharedWeaponList::iterator;

// �����їp(�������)��ؽč쐬
using SharedWeaponInventoryPtr = shared_ptr<ItemBase>;
using SharedWeaponInventoryList = list<SharedWeaponInventoryPtr>;
using SharedWeaponInventoryListPtr = shared_ptr<SharedWeaponInventoryList>;

using WeakWeaponInventoryList = weak_ptr<SharedWeaponInventoryList>;
using SharedWeaponInventoryListItr = SharedWeaponInventoryList::iterator;

// ؽĂւ̒ǉ�
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

// �G����ؽĂւ̒ǉ�
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


// ؽĂւ̒ǉ�
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

// ؽĂւ̒ǉ�
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