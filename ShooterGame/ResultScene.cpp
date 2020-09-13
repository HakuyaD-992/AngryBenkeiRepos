#include <DxLib.h>

#include "ResultScene.h"
#include "Input.h"

#include "SceneController.h"
#include "TitleScene.h"
#include "ImageManager.h"
#include "Application.h"

ResultScene::ResultScene(SceneController& sCon, int useBullet, bool winFlag) :
	BaseScene(sCon)
{
	this->useBullet = useBullet;
	this->winFlag = winFlag;
	Initialize();
}

ResultScene::~ResultScene()
{

}

void ResultScene::UpDate(const std::vector<std::shared_ptr<Input>>& input)
{
	auto inputData = input[static_cast<int>(PLAYER::ONE)]->GetPeriData();

	for (auto in : inputData)
	{
		if (in.first == KeyConfiguration::Decision)
		{
			if (in.second[static_cast<int>(TrgFlag::Now)] && !in.second[static_cast<int>(TrgFlag::Old)])
			{
				sceneCtl_.CleanupAndChangewScene(std::make_shared<TitleScene>(sceneCtl_));
			}
		}
	}
}

void ResultScene::Initialize(void)
{
	lpImage.Load("Result/result");
}

void ResultScene::Draw(void)
{
	auto& app = Application::Instance();
	ClearDrawScreen();
	DrawRotaGraph(app.GetViewport().GetSize().x / 2,
		30, 1.0f, 0.0f,
		lpImage.GetID("Result/result"),
		true, false);
	if (winFlag)
	{
		DrawGraph(400 - 187, 100, lpImage.GetID("Result/gameclear"), true);
	}
	else
	{
		DrawGraph(400 - 175, 100, lpImage.GetID("Result/gameover"), true);
	}

	DrawGraph(0, 300, lpImage.GetID("Result/total"), true);

	if (useBullet < 10)
	{
		DrawGraph(525, 300, lpImage.GetDivID("Result/number")[useBullet], true);
	}

	if (useBullet > 9 && useBullet < 100)
	{
		DrawGraph(525, 300, lpImage.GetDivID("Result/number")[useBullet / 10], true);
		DrawGraph(525 + 43, 300, lpImage.GetDivID("Result/number")[useBullet % 10], true);
	}

	if (useBullet > 99 && useBullet < 1000)
	{
		DrawGraph(525, 300, lpImage.GetDivID("Result/number")[useBullet / 100], true);
		DrawGraph(525 + 43, 300, lpImage.GetDivID("Result/number")[(useBullet % 100) / 10], true);
		DrawGraph(525 + 86, 300, lpImage.GetDivID("Result/number")[useBullet % 10], true);
	}

	if (useBullet > 999 && useBullet < 10000)
	{
		DrawGraph(525, 300, lpImage.GetDivID("Result/number")[useBullet / 1000], true);
		DrawGraph(525 + 43, 300, lpImage.GetDivID("Result/number")[(useBullet % 1000) / 100], true);
		DrawGraph(525 + 86, 300, lpImage.GetDivID("Result/number")[(useBullet % 100) / 10], true);
		DrawGraph(525 + 129, 300, lpImage.GetDivID("Result/number")[useBullet % 10], true);
	}

	if (useBullet > 9999 && useBullet < 100000)
	{
		DrawGraph(525, 300, lpImage.GetDivID("Result/number")[useBullet / 10000], true);
		DrawGraph(525 + 43, 300, lpImage.GetDivID("Result/number")[(useBullet % 10000) / 1000], true);
		DrawGraph(525 + 86, 300, lpImage.GetDivID("Result/number")[(useBullet % 1000) / 100], true);
		DrawGraph(525 + 129, 300, lpImage.GetDivID("Result/number")[(useBullet % 100) / 10], true);
		DrawGraph(525 + 172, 300, lpImage.GetDivID("Result/number")[useBullet % 10], true);
	}
	DrawFormatString(0, 0, 0xffffff, "%d", useBullet);
	ScreenFlip();
}
