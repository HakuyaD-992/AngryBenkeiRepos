#pragma once

#include "ItemBase.h"
#include "SceneShift.h"

class Item_Weapon :
	public ItemBase
{
public:
	Item_Weapon(Vector2 pos,Vector2 size,WEAPON type);
	~Item_Weapon();
	
	void Move(WeakList charaList);

private:
	bool Init(void);

	bool moveF;



};

