#pragma once
#include "BaseScene.h"
class Title :
	public BaseScene
{
public:
	Title();
	~Title();

	// update scene
	ScenePtr SceneUpDate(ScenePtr own, const PlayerController& gameCtl);
	// initialize
	bool Init(void);
	// draw something in this scene
	void Draw(void);
	// draw debug message
	void DebugDraw(void);
private:

};

