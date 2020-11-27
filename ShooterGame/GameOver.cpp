#include <DxLib.h>
#include "GameOver.h"
#include "SceneController.h"
#include "Input.h"
#include "ImageManager.h"
#include "TitleScene.h"
#include "Application.h"
#include "SoundManager.h"

GameOver::GameOver(SceneController& sCon):
	BaseScene(sCon)
{
	Initialize();
	lpSound.Play("GameOver", DX_PLAYTYPE_BACK);
}

GameOver::~GameOver()
{
}

void GameOver::UpDate(const std::vector<std::shared_ptr<Input>>& input)
{
	shakeFrame_++;
	logoFlickCnt_++;

	auto inputData = input[static_cast<int>(PLAYER::ONE)]->GetPeriData();
	if (shakeFrame_ % 30 / 2 == 0)
	{
		logoShakeRate_ = -4 + GetRand(8);
	}
	if (fade_ == Fade::In)
	{
		fadeCnt_++;
		if (fadeCnt_ >= 255)
		{
			fade_ = Fade::Out;
			//fadeCnt_ = 255;
		}
	}
	else
	{
		fadeCnt_backtotitle++;

	}
	for (auto in : inputData)
	{
		if (in.first == KeyConfiguration::Decision)
		{
			if (in.second[static_cast<int>(TrgFlag::Now)] && !in.second[static_cast<int>(TrgFlag::Old)])
			{
				littleExtendFlag_ = true;
				lpSound.Play("BacktoTitle", DX_PLAYTYPE_BACK);
				returnTitleFlag_ = true;
			}
		}
	}

	if (!returnTitleFlag_)
	{
		if (littleExtendFlag_)
		{
			exRate_ += 0.01f;
			if (exRate_ >= 1.5f)
			{
				returnTitleFlag_ = true;
			}
		}
	}

	if (returnTitleFlag_)
	{
		exRate_ -= 0.02f;
		if (exRate_ <= 0.0f)
		{
			sceneCtl_.CleanupAndChangewScene(std::make_shared<TitleScene>(sceneCtl_));
		}
	}

	/*if (returnTitleFlag_)
	{
		if (brightFlag_)
		{
			pushAddval_+=10.0f;
			if (pushAddval_ >= 255.0f)
			{
				brightFlag_ = false;
			}
		}
		else
		{
			pushAddval_-=20.0f;
			if (pushAddval_ <= 0.0f)
			{
				sceneCtl_.CleanupAndChangewScene(std::make_shared<TitleScene>(sceneCtl_));
			}
		}
	}*/
}

void GameOver::Draw(void)
{
	ClearDrawScreen();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeCnt_);
	DrawRotaGraph(logoPos_.x + logoShakeRate_, logoPos_.y + logoShakeRate_, exRate_ , 0.0f, lpImage.GetID("Result/gameover"), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetDrawBright(pushAddval_, pushAddval_, pushAddval_);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeCnt_backtotitle);
	DrawRotaGraph(logoPos_.x, logoPos_.y + 150, exRate_, 0.0f, lpImage.GetID("Result/BacktoTitle"), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetDrawBright(255, 255, 255);

	ScreenFlip();
}

void GameOver::Initialize(void)
{
	auto& app = Application::Instance();
	auto scr = app.GetViewport().GetSize();
	logoPos_ = { scr.x / 2, scr.y/2 - 50 };
	logoShakeRate_ = 0;
	logoFlickCnt_ = 0;
	fadeCnt_ = 0;
	fadeCnt_backtotitle = 0;
	shakeFrame_ = 0;
	pushAddval_ = 100.0f;
	littleExtendFlag_ = false;
	returnTitleFlag_ = false;
	brightFlag_ = true;
	exRate_ = 1.0f;
	fade_ = Fade::In;
}
