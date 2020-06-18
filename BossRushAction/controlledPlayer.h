#pragma once
#include "BasePlayer.h"

class controlledPlayer :
	public BasePlayer
{
public:
	controlledPlayer(Vector2 pos,ANIMATION anim,DIRECTION direction);
	~controlledPlayer();

	void Action(const GameController& gameCtl, WeakEnemyList enemyList);

private:
	void Draw(void);
	void Init(void);

	void AnimationInit(void);
	void Jump(void);
	void Attack(const GameController& gameCtl, WeakEnemyList enemyList);
	void HitAttack(WeakEnemyList enemyList);
	void KnockBack(WeakEnemyList enemyList);

	void DeleteShot(void);

	void BoxColliderUpDate(void);

	bool canAttack;
	int shotCount;

	DIRECTION enemyDir;
	DIRECTION shotDir;
};

