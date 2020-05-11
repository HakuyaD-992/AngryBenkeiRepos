#include <DxLib.h>

#include "GameController.h"
#include "GameClear.h"
#include "SceneShift.h"
#include "Result.h"
#include "Title.h"


GameClear::GameClear()
{
	Init();
}


GameClear::~GameClear()
{
}

ScenePtr GameClear::SceneUpDate(ScenePtr own, const PlayerController & gameCtl)
{
	auto padNow = gameCtl[Player_1]->GetPadInfo().padInputNow;
	auto padOld = gameCtl[Player_1]->GetPadInfo().padInputOld;


	Draw();
	return move(own);
}

bool GameClear::Init(void)
{
	lpScene.GetSceneState() = StateGameClear;
	return true;
}

void GameClear::Draw(void)
{
	ClsDrawScreen();
	DebugDraw();
	ScreenFlip();
}

void GameClear::DebugDraw(void)
{
	DrawFormatString(0, 0, 0xffffff, "GameClear");
}
