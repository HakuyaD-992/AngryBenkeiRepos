
#include <DxLib.h>
#include "GameOver.h"
#include "Title.h"
#include "GameController.h"



GameOver::GameOver()
{
	Init();
}


GameOver::~GameOver()
{
}

ScenePtr GameOver::SceneUpDate(ScenePtr own, const PlayerController & gameCtl)
{
	// input information(Gamepad)
	auto inputNow = gameCtl[Player_1]->GetPadInfo().padInputNow;
	auto inputOld = gameCtl[Player_1]->GetPadInfo().padInputOld;

	if (inputNow[11] && !inputOld[11])
	{
		return std::make_unique<Title>();
	}
	ClearDrawScreen();
	Draw();
	ScreenFlip();
	return move(own);
}

bool GameOver::Init(void)
{
	return true;
}

void GameOver::Draw(void)
{

	DrawFormatString(ScrSize.x / 2 - 50, ScrSize.y / 2 - 50, 0xffffff, "GameOver");
	DrawFormatString(ScrSize.x / 2 - 50, ScrSize.y / 2 + 50, 0xffffff, "Push start:return title");

}

void GameOver::DebugDraw(void)
{
}
