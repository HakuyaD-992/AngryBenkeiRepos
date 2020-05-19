#pragma once

#include "Vector2.h"
#include "ENEMYTYPE.h"
#include "EnemyAnimation.h"

class BaseEnemy
{
public:
	BaseEnemy();
	~BaseEnemy();

	virtual void UpDate(void);
	virtual void Action(void) = 0;

private:



protected:
	// position
	Vector2 pos;
	// type of enemy
	ENEMYTYPE type;


};

