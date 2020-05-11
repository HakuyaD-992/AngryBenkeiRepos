#pragma once
#include "BaseScene.h"
class Result :
	public BaseScene
{
public:
	Result();
	~Result();
	ScenePtr SceneUpDate(ScenePtr own, const PlayerController& gameCtl);
private:
	bool Init(void);
	void Draw(void);
	void DebugDraw(void);
};

