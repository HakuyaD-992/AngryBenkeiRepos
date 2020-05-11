#include <DxLib.h>

#include "Tutorial.h"
#include "SceneShift.h"
#include "GamePlay.h"

#include "GameController.h"

Tutorial::Tutorial()
{
	Init();
}


Tutorial::~Tutorial()
{
}

ScenePtr Tutorial::SceneUpDate(ScenePtr own, const PlayerController & gameCtl)
{
	auto padNow = gameCtl[Player_1]->GetPadInfo().padInputNow;
	auto padOld = gameCtl[Player_1]->GetPadInfo().padInputOld;

	Draw();

	return move(own);
}

bool Tutorial::Init(void)
{
	// state•Ï”‚ğtutorial‚É
	lpScene.GetSceneState() = StateTutorial;

	return true;
}

void Tutorial::Draw(void)
{
	ClsDrawScreen();
	DebugDraw();
	ScreenFlip();
}

void Tutorial::DebugDraw(void)
{
	DrawFormatString(0, 0, 0xffffff, "Tutorial");
}
