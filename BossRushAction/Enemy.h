#pragma once
#include "BaseEnemy.h"

enum AI_FLAG
{
	// standard running
	AI_Run,
	// move forward to player
	AI_MoveForward,
	// go around
	AI_GoAround,
	// ready mode
	AI_Idle,
	// attack
	AI_Attack,
	// avoid player's attack
	AI_AvoidAttacking,
	AI_Max
};


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
	// knock back
	void KnockBack(WeakPlayerList playerList);
	void Jump(WeakPlayerList playerList);
	void HitAttack(WeakPlayerList playerList);

	void AIAction(Vector2 distance);

	void MoveForwardtoPlayer(void);
	void MoveBehindtoPlayer(Vector2 distance);
	bool Init(void);

	// update box collider position
	void BoxColliderUpDate(void);
	// player's direction
	DIRECTION playerDir;

	AI_FLAG motionFlag;
};

