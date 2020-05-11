#pragma once
#include "BaseScene.h"
class GameOver :
	public BaseScene
{
public:
	GameOver();
	~GameOver();
	ScenePtr SceneUpDate(ScenePtr own, const PlayerController& gameCtl);
private:
	bool Init(void);
	void Draw(void);
	void DebugDraw(void);
};

