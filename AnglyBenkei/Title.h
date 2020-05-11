#pragma once
#include "BaseScene.h"

class Title :
	public BaseScene
{
public:
	Title();
	~Title();
	// ¼°İ±¯ÌßÃŞ°Ä
	ScenePtr SceneUpDate(ScenePtr own, const PlayerController& gameCtl);
	// À²ÄÙÛºŞ‚ÌÎß¼Ş¼®İ“™‚ÌXV
	void TitleLogoUpDate(void);


private:
	// ‰Šú‰»ŠÖŒWŠÖ”
	bool Init(void);
	// •`‰æŠÖŒWŠÖ”
	void Draw(void);
	// ÃŞÊŞ¯¸Ş•\¦ŠÖ”
	void DebugDraw(void);
	// À²ÄÙÛºŞ‚Ì•`‰æ
	void TitleLogoDraw(void);
	// À²ÄÙÛºŞ‚ÌÎß¼Ş¼®İ
	Vector2 titleLogoPos;

	int debugFlag;
};

