#include <DxLib.h>
#include "Title.h"
#include "GamePlay.h"
#include "GameController.h"


Title::Title()
{
	Init();
}


Title::~Title()
{
}

ScenePtr Title::SceneUpDate(ScenePtr own, const PlayerController & gameCtl)
{
	// input information(gamepad)
	auto inputNow = gameCtl[Player_1]->GetPadInfo().padInputNow;
	auto inputOld = gameCtl[Player_1]->GetPadInfo().padInputOld;

	// if you push "start", youll go to "GamePlay"
	if (inputNow[11] && !inputOld[11])
	{
		return std::make_unique<GamePlay>();
	}

	// draw something
	Draw();

	return move(own);
}

bool Title::Init(void)
{
	return true;
}

void Title::Draw(void)
{
	// clear screen
	ClearDrawScreen();

	// draw debug message
	DebugDraw();
	// debug
	DrawFormatString(0, 0, 0xffffff, "Title");

	// flip screen
	ScreenFlip();
}

void Title::DebugDraw(void)
{
}
