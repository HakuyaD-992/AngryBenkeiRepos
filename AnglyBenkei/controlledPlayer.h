#pragma once
#include "BasePlayer.h"
#include "GameController.h"

class controlledPlayer :
	public BasePlayer
{
public:
	controlledPlayer(Vector2 pos,ANIMATION anim,Vector2 size);
	~controlledPlayer();

	void Draw(void);
	void Init(void);
	void Action(const GameController& gameCtl, WeakWeaponList item);
private:
	// ���했�̱�Ұ��݂̏�����(�����Ɍ����ƁA�U��Ӱ��݂����했�ɈႤ�̂ōU����Ұ��݂�����ʁX�ɏ���������������)
	bool InitAnimation(WEAPON weapon);
	// 1�ڰёO�̍U����
	int oldAttackCount;
};

