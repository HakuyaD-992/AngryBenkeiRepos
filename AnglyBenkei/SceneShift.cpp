#include <DxLib.h>

#include "SceneShift.h"
#include "Title.h"
#include "GameController.h"

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
		// 1ﾌﾚｰﾑ前のstate状態を保存しておく
		oldState = nowState;
		// 今格納されているｹﾞｰﾑﾊﾟｯﾄﾞでｹﾞｰﾑﾊﾟｯﾄﾞの更新
		for (auto pCon = playerController.begin(); pCon != playerController.end(); pCon++)
		{
			(*pCon)->Update();
		}
		// ｼｰﾝの移行(ｼｰﾝを移行させるのは1PのｺﾝﾄﾛｰﾗｰだけなのでｺﾝﾄﾛｰﾗｰはPlayer_1のみ)
		scenePtr = scenePtr->SceneUpDate(move(scenePtr),playerController);

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
	sceneins = new SceneShift();
}

bool SceneShift::SystemInit(void)
{
	SetGraphMode(Screen_x, Screen_y, 32);
	ChangeWindowMode(true);
	SetWindowText("AnglyBenkei");
	if (DxLib_Init() == 1)
	{
		return false;
	}

	// 1Pのｺﾝﾄﾛｰﾗｰは最初にｲﾝｽﾀﾝｽしておく
	playerController.push_back(new GameController(Player_1));
	nowState = StateTitle;
	oldState = nowState;
	return true;
}
