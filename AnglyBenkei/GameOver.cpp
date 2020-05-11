#include <DxLib.h>

#include "GameController.h"
#include "SceneShift.h"
#include "Title.h"
#include "GameOver.h"



GameOver::GameOver()
{
}


GameOver::~GameOver()
{
}

ScenePtr GameOver::SceneUpDate(ScenePtr own, const PlayerController & gameCtl)
{
	auto padNow = gameCtl[Player_1]->GetPadInfo().padInputNow;
	auto padOld = gameCtl[Player_1]->GetPadInfo().padInputOld;

	Draw();
	return move(own);
}

bool GameOver::Init(void)
{
	lpScene.GetSceneState() = StateGameOver;
	return true;
}

void GameOver::Draw(void)
{
	ClsDrawScreen();
	DebugDraw();
	ScreenFlip();
}

void GameOver::DebugDraw(void)
{
	DrawFormatString(0, 0, 0xffffff,"GameClear");
}
