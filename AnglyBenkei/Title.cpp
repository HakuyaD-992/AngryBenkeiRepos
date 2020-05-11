#include <DxLib.h>


#include "SceneShift.h"
#include "Title.h"
#include "Tutorial.h"
#include "GameController.h"
#include "GamePlay.h"

Title::Title()
{
	Init();
}


Title::~Title()
{
}

ScenePtr Title::SceneUpDate(ScenePtr own, const PlayerController & gameCtl)
{
	auto padNow = gameCtl[Player_1]->GetPadInfo().padInputNow;
	auto padOld = gameCtl[Player_1]->GetPadInfo().padInputOld;

	if (padNow[10] && !padOld[10])
	{
		return std::make_unique<GamePlay>();
	}


	Draw();
	return move(own);
}

void Title::TitleLogoUpDate(void)
{
}

bool Title::Init(void)
{
	debugFlag = false;
	lpScene.GetSceneState() = StateTitle;
	return true;
}

void Title::Draw(void)
{
	ClsDrawScreen();
	DebugDraw();
	ScreenFlip();
}

void Title::DebugDraw(void)
{
	DrawFormatString(0, 0, 0xffffff, "Title");
	if (debugFlag)
	{
		DrawFormatString(100, 100, 0xffffff, "true");
	}
	else
	{
		DrawFormatString(100, 100, 0xffffff, "false");
	}


	// �ް��߯�ނ̊e���ݔԍ��m�F�p         
	int Pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);        //���͏�Ԃ�Pad�Ɋi�[
	for (int i = 0; i < 28; i++)
	{
		//�{�^��28�����[�v
		if (Pad & (1 << i))
		{
			//�{�^��i�̓��̓t���O�������Ă�����
			DrawFormatString(0, i * 15, GetColor(255, 255, 255), "%d�̃L�[��������Ă��܂�", i);
		}
	}
}

void Title::TitleLogoDraw(void)
{
}
