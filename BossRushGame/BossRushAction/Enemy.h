#pragma once
#include "BaseEnemy.h"
class Enemy :
	public BaseEnemy
{
public:
	Enemy(Vector2 pos,EnemyAnimation anim,ENEMYTYPE type,DIRECTION direction);
	~Enemy();

	void Action(WeakPlayerList playerList);
	void Draw(void);

private:
	// initialize animations
	bool AnimationInit(ENEMYTYPE eType);
	// move enemy right or left
	void Run(void);
};

