#pragma once
#include "BaseScene.h"
class GameClear :
	public BaseScene
{
public:
	GameClear();
	~GameClear();
	ScenePtr SceneUpDate(ScenePtr own, const PlayerController& gameCtl);
private:
	bool Init(void);
	void Draw(void);
	void DebugDraw(void);
};

