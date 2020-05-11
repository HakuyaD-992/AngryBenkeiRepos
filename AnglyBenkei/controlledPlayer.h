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
	// 武器毎のｱﾆﾒｰｼｮﾝの初期化(厳密に言うと、攻撃ﾓｰｼｮﾝが武器毎に違うので攻撃ｱﾆﾒｰｼｮﾝだけを別々に初期化したいため)
	bool InitAnimation(WEAPON weapon);
	// 1ﾌﾚｰﾑ前の攻撃回数
	int oldAttackCount;
};

