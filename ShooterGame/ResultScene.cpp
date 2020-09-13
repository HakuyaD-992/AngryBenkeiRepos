#include <DxLib.h>

#include "ResultScene.h"
#include "Input.h"
#include "SceneController.h"
#include "TitleScene.h"
#include "ImageManager.h"
#include "Application.h"

ResultScene::ResultScene(SceneController& sCon):
	BaseScene(sCon)
{
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
	ScreenFlip();
}
