#pragma once
#include "BaseScene.h"
class Tutorial :
	public BaseScene
{
public:
	Tutorial();
	~Tutorial();

	ScenePtr SceneUpDate(ScenePtr own, const PlayerController& gameCtl);

private:
	// ϊ»ΦWΦ
	bool Init(void);
	// `ζΦWΦ
	void Draw(void);
	// ΓήΚή―Έή`ζΦWΦ
	void DebugDraw(void);
};

