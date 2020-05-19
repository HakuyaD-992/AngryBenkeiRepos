#pragma once
#include "BasePlayer.h"
class controlledPlayer :
	public BasePlayer
{
public:
	controlledPlayer(Vector2 pos,ANIMATION anim,DIRECTION direction);
	~controlledPlayer();

	void Action(const GameController& gameCtl);


private:
	void Draw(void);

	void AnimationInit(void);
	void Jump(void);
	void Attack(const GameController& gameCtl);
};

