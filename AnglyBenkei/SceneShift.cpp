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
		// 1�ڰёO��state��Ԃ�ۑ����Ă���
		oldState = nowState;
		// ���i�[����Ă���ް��߯�ނŹް��߯�ނ̍X�V
		for (auto pCon = playerController.begin(); pCon != playerController.end(); pCon++)
		{
			(*pCon)->Update();
		}
		// ��݂̈ڍs(��݂��ڍs������̂�1P�̺��۰װ�����Ȃ̂ź��۰װ��Player_1�̂�)
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

	// 1P�̺��۰װ�͍ŏ��ɲݽ�ݽ���Ă���
	playerController.push_back(new GameController(Player_1));
	nowState = StateTitle;
	oldState = nowState;
	return true;
}
