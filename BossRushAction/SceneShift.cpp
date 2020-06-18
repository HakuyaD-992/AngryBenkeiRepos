#include <DxLib.h>


#include "Title.h"
#include "GameController.h"
#include "SceneShift.h"

std::once_flag SceneShift::onceflag;
SceneShift* SceneShift::sceneins = nullptr;

void SceneShift::Destroy(void)
{
	if (sceneins != nullptr)
	{
		delete sceneins;
	}
	sceneins = nullptr;
}

void SceneShift::onceRun(void)
{
	scenePtr = std::make_unique<Title>();
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// update registered gamecontroller at now
		for (auto pCon = playerController.begin(); pCon != playerController.end(); pCon++)
		{
			(*pCon)->Update();
		}
		// update scene(all)
		scenePtr = scenePtr->SceneUpDate(move(scenePtr), playerController);
	}

}

SceneShift::SceneShift()
{
	SystemInit();
}


SceneShift::~SceneShift()
{
}

void SceneShift::Create(void)
{
	if (sceneins == nullptr)
	{
		sceneins = new SceneShift();
	}
}

bool SceneShift::SystemInit(void)
{
	SetGraphMode(Screen_x, Screen_y, 32);
	ChangeWindowMode(true);
	SetWindowText("BossRushGame");
	if (DxLib_Init() == 1)
	{
		return false;
	}

	// intialize Player1's controller at first
	playerController.push_back(new GameController(Player_1));

	return true;
}
