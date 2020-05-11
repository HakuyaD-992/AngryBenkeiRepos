#pragma once
#include <list>
#include <memory>

class BasePlayer;
class ItemBase;

using namespace std;

// ｹﾞｰﾑ登場ｷｬﾗｸﾀｰ用のﾘｽﾄ作成
using SharedPtr = shared_ptr<BasePlayer>;
using SharedList = list<SharedPtr>;
using SharedListPtr = shared_ptr<SharedList>;

using WeakList = weak_ptr<SharedList>;
using SharedListItr = SharedList::iterator;

// 武器ｱｲﾃﾑ用のﾘｽﾄ作成
using SharedWeaponPtr = shared_ptr<ItemBase>;
using SharedWeaponList = list<SharedWeaponPtr>;
using SharedWeaponListPtr = shared_ptr<SharedWeaponList>;

using WeakWeaponList = weak_ptr<SharedWeaponList>;
using SharedWeaponListItr = SharedWeaponList::iterator;

// 武器ｱｲﾃﾑ用(ｲﾝﾍﾞﾝﾄﾘ)のﾘｽﾄ作成
using SharedWeaponInventoryPtr = shared_ptr<ItemBase>;
using SharedWeaponInventoryList = list<SharedWeaponInventoryPtr>;
using SharedWeaponInventoryListPtr = shared_ptr<SharedWeaponInventoryList>;

using WeakWeaponInventoryList = weak_ptr<SharedWeaponInventoryList>;
using SharedWeaponInventoryListItr = SharedWeaponInventoryList::iterator;

// ﾘｽﾄへの追加
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

// ﾘｽﾄへの追加
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

// ﾘｽﾄへの追加
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