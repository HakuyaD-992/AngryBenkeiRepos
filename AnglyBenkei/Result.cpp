#include <DxLib.h>

#include "GameController.h"
#include "SceneShift.h"
#include "Result.h"
#include "Title.h"



Result::Result()
{
}

Result::~Result()
{
}

ScenePtr Result::SceneUpDate(ScenePtr own, const PlayerController & gameCtl)
{
	auto padNow = gameCtl[Player_1]->GetPadInfo().padInputNow;
	auto padOld = gameCtl[Player_1]->GetPadInfo().padInputOld;

	Draw();
	return move(own);
}

bool Result::Init(void)
{
	// ¼°İó‘Ô‚ğResult‚Éİ’è
	lpScene.GetSceneState() = StateResult;
	return true;
}

void Result::Draw(void)
{
	ClsDrawScreen();
	DebugDraw();
	ScreenFlip();
}

void Result::DebugDraw(void)
{
	DrawFormatString(0, 0, 0xffffff, "Result");
}
