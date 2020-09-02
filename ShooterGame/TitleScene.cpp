#include "TitleScene.h"
#include "PlayScene.h"
#include "PLAYER.h"
#include "Input.h"
#include "Application.h"
#include "ImageManager.h"
#include "EffectManager.h"
#include "SceneController.h"


TitleScene::TitleScene(SceneController& sCon):
	BaseScene(sCon)
{
	Initialize();
}

TitleScene::~TitleScene()
{
}

void TitleScene::UpDate(const std::vector<std::shared_ptr<Input>>& input)
{
	auto inputData1_ = input[static_cast<int>(PLAYER::ONE)]->GetPeriData();
	auto inputData2_ = input[static_cast<int>(PLAYER::TWO)]->GetPeriData();


	lpEffect.UpDate();

	stringSp_[0].y++;
	if (stringSp_[0].y >= 100)
	{
		stringSp_[0].y = 100;
	}
	stringSp_[1].y++;
	if (stringSp_[1].y >= 170)
	{
		stringSp_[1].y = 170;
	}


	if (fade_ == Fade::In)
	{
		fadeCnt_ += 2;
	}
	if (fadeCnt_ >= 255)
	{
		fadeCnt_ = 255;
	}
	if (fadeCnt_ >= 255)
	{
		for (auto cnt : inputData1_)
		{
			if (cnt.first == KeyConfiguration::Down)
			{
				if (cnt.second[static_cast<int>(TrgFlag::Now)] &&
					!cnt.second[static_cast<int>(TrgFlag::Old)])
				{
					arrowPos_.y += 70;
					if (arrowPos_.y >= stringPos_.y + 70)
					{
						arrowPos_.y = stringPos_.y + 70;
					}
					nextFlag_ = Next::Manual;
				}
			}
			if (cnt.first == KeyConfiguration::Up)
			{
				if (cnt.second[static_cast<int>(TrgFlag::Now)] &&
					!cnt.second[static_cast<int>(TrgFlag::Old)])
				{
					arrowPos_.y -= 70;
					if (arrowPos_.y <= stringPos_.y)
					{
						arrowPos_.y = stringPos_.y;
					}
					nextFlag_ = Next::Game;
				}
			}

			if (cnt.first == KeyConfiguration::Decision)
			{
				if (cnt.second[static_cast<int>(TrgFlag::Now)] &&
					!cnt.second[static_cast<int>(TrgFlag::Old)])
				{
					lpEffect.Play("thunder", Vector2I(arrowPos_.x + 120, arrowPos_.y + 120));
					isNext_ = true;
				}
			}
		}
	}
	if (isNext_)
	{
		if (nextFlag_ == Next::Manual && (lpEffect.IsPlayingEffect("thunder") == -1))
		{
			//return std::make_unique<>
		}
		// �ްѽ���
		if (nextFlag_ == Next::Game && (lpEffect.IsPlayingEffect("thunder") == -1))
		{
			sceneCtl_.ChangeScene(std::make_shared<PlayScene>(sceneCtl_));
		}
	}
	if (lpEffect.IsPlayingEffect("thunder") == 0)
	{
		int i = 0;
	}


	// 2P�Q��
	/*if (inputData2_[KeyConfiguration::Decision][static_cast<int>(TrgFlag::Now)] &&
		inputData2_[KeyConfiguration::Decision][static_cast<int>(TrgFlag::Old)])
	{
		isConnected = true;
	}*/

}

void TitleScene::Draw(void)
{
	auto& app = Application::Instance();
	ClearDrawScreen();
	int col = 0;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeCnt_);
	DrawGraph(stringPos_.x, stringPos_.y, lpImage.GetID("Title/title"), true);
	DrawGraph(arrowPos_.x, arrowPos_.y + stringSp_[0].y, lpImage.GetID("Title/arrow"), true);

	DrawGraph(stringPos_.x + 50, stringPos_.y + stringSp_[0].y, lpImage.GetID("Title/start"), true);
	DrawGraph(stringPos_.x + 50, stringPos_.y + stringSp_[1].y, lpImage.GetID("Title/manual"), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	lpEffect.Draw();

	ScreenFlip();
}

void TitleScene::Initialize(void)
{
	auto& app = Application::Instance();

	stringPos_ = { app.GetViewport().GetSize().x / 2, app.GetViewport().GetSize().y / 2 - 100 };
	// �����߼޼��
	arrowPos_ = { stringPos_.x - 20,stringPos_.y };

	nextFlag_ = Next::Game;
	isNext_ = false;

	// �摜��۰��
	lpImage.Load("Title/title");
	lpImage.Load("Title/start");
	lpImage.Load("Title/manual");
	lpImage.Load("Title/arrow");

	// �̪�Ă�۰��
	lpEffect.Load("thunder");

	for (int i = 0; i < 2; i++)
	{
		stringSp_[i] = { 1,1 };
	}

	// ̪��޶��Ă̏�����
	fadeCnt_ = 0;
	fade_ = Fade::In;
	//return true;
}

