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
	// ‰Šú‰»ŠÖŒWŠÖ”
	bool Init(void);
	// •`‰æŠÖŒWŠÖ”
	void Draw(void);
	// ÃŞÊŞ¯¸Ş•`‰æŠÖŒWŠÖ”
	void DebugDraw(void);
};

