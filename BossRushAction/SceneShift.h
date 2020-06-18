#pragma once
#include <mutex>

#include "BaseScene.h"
#include "Vector2.h"

// ¡Œ»İ‚Ì¼°İó‘Ô•Ï”
enum SceneState
{
	// À²ÄÙ
	StateTitle,
	// Á­°ÄØ±Ù
	StateTutorial,
	// ¹Ş°ÑÌßÚ²
	StateGame,
	// ¹Ş°Ñµ°ÊŞ°
	StateGameOver,
	// ¹Ş°Ñ¸Ø±
	StateGameClear,
	// Ø»ŞÙÄ(×İ·İ¸Ş“o˜^)
	StateResult,
	StateMax
};

// ‰æ–Ê‚Ì‰¡»²½Ş
#define Screen_x 960
// ‰æ–Ê‚Ìc»²½Ş
#define Screen_y 560

#define lpScene SceneShift::getInstance()

class BaseScene;

class SceneShift
{
public:
	static void Destroy(void);
	static SceneShift &getInstance(void)
	{
		Create();
		return *sceneins;
	}
	void onceRun(void);


	// ‰æ–Ê»²½Şæ“¾ŠÖ”
	const Vector2 GetScreenSize()
	{
		return Vector2(Screen_x, Screen_y);
	}


private:
	SceneShift();
	~SceneShift();

	static std::once_flag onceflag;
	static SceneShift* sceneins;

	static void Create(void);

	bool(SceneShift::*s_ptr)(void);

	// DxLibŠÖŒW‚Ì‰Šú‰»ŠÖ”
	bool SystemInit(void);

	// ¼°İ–ˆ‚ÌÎß²İÀ
	ScenePtr scenePtr;
	// ¹Ş°ÑºİÄÛ°×°•Ï”(²İ½Àİ½—p)
	PlayerController playerController;

};

