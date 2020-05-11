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
	// •Ší–ˆ‚Ì±ÆÒ°¼®İ‚Ì‰Šú‰»(Œµ–§‚ÉŒ¾‚¤‚ÆAUŒ‚Ó°¼®İ‚ª•Ší–ˆ‚Éˆá‚¤‚Ì‚ÅUŒ‚±ÆÒ°¼®İ‚¾‚¯‚ğ•ÊX‚É‰Šú‰»‚µ‚½‚¢‚½‚ß)
	bool InitAnimation(WEAPON weapon);
	// 1ÌÚ°Ñ‘O‚ÌUŒ‚‰ñ”
	int oldAttackCount;
};

