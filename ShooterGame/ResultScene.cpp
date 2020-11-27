#include <DxLib.h>

#include "ResultScene.h"
#include "Input.h"

#include "SceneController.h"
#include "TitleScene.h"
#include "ImageManager.h"
#include "Application.h"
#include "SoundManager.h"

ResultScene::ResultScene(SceneController& sCon, int useBullet,
	time_t& frame,int& defeatEnemy) :
	BaseScene(sCon)
{
	Initialize();

	this->useBullet = (float)useBullet;
	clearTime_ = frame;
	totalDefeatEnemyNum_ = (float)defeatEnemy;
	hitRate_ = (totalDefeatEnemyNum_ / this->useBullet) * 100.0f;
	// ¸Ø±À²Ñ‚Ì•ª
	clearTime_t = clearTime_ / 60;
	// ¸Ø±À²Ñ‚Ì•b1Œ…–Ú
	clearTime_secf1 = clearTime_ % 60 / 10;
	// ¸Ø±À²Ñ‚Ì•b2Œ…–Ú
	clearTime_secf2 = clearTime_ % 60 % 10;

	totalScore_ = hitRate_ * 8 * clearTime_;

	lpSound.Play("Result", DX_PLAYTYPE_BACK);

}

ResultScene::~ResultScene()
{

}

void ResultScene::UpDate(const std::vector<std::shared_ptr<Input>>& input)
{
	auto inputData = input[static_cast<int>(PLAYER::ONE)]->GetPeriData();

	(this->*updater_)();

	for (auto in : inputData)
	{
		if (in.first == KeyConfiguration::Decision)
		{
			if (in.second[static_cast<int>(TrgFlag::Now)] && !in.second[static_cast<int>(TrgFlag::Old)])
			{
				lpSound.Stop("Result");
				sceneCtl_.CleanupAndChangewScene(std::make_shared<TitleScene>(sceneCtl_));
			}
		}
	}

	if (!lpSound.CheckPlaySound("Result"))
	{
		lpSound.Stop("Result");
		sceneCtl_.CleanupAndChangewScene(std::make_shared<TitleScene>(sceneCtl_));
	}

}

void ResultScene::Initialize(void)
{
	auto& app = Application::Instance();
	auto scr = app.GetViewport().GetSize();
	updater_ = &ResultScene::FirstUpdate;
	strType_ = StringType::Time;

	drawPercentFlag_ = false;
	for (int i = 0; i < 3; i++)
	{
		lineAlphaval_[i] = 0.0f;
		box_end[i] = -10;
		playSeFlag_[i] = true;
	}
	lpImage.Load("Result/result");
	lpImage.Load("Result/timeDot");
	stringSpeed_ = 3;
	hitRate_ = 0.0f;
	volPan_ = 70.0f;
	stringPos_[static_cast<int>(StringType::Time)]
		= { -300,scr.y / 2 - 150 };

	stringPos_[static_cast<int>(StringType::HitRate)]
		= { -200,scr.y / 2 - 80 };

	percentPos_ = { stringPos_[static_cast<int>(StringType::HitRate)].x,
					stringPos_[static_cast<int>(StringType::HitRate)].y + 50 };

	stringPos_[static_cast<int>(StringType::Score)]
		= { -400,scr.y / 2 + 100 };

	stringPos_[static_cast<int>(StringType::PushB)]
		= { scr.x/2,scr.y / 2 +100 };

	fadeCnt_ = { 0,0,0,0 };
}

void ResultScene::Draw(void)
{
	auto& app = Application::Instance();
	ClearDrawScreen();
	DrawRotaGraph(app.GetViewport().GetSize().x / 2,
		30, 1.0f, 0.0f,
		lpImage.GetID("Result/result"),
		true, false);

	SetDrawBlendMode(DX_BLENDMODE_ADD, lineAlphaval_[0]);
	DrawBox(-10, stringPos_[static_cast<int>(StringType::Time)].y - 30,
		box_end[0], stringPos_[static_cast<int>(StringType::Time)].y + 30,
		0xffffff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawRotaGraph(stringPos_[static_cast<int>(StringType::Time)].x,
		stringPos_[static_cast<int>(StringType::Time)].y, 1.0f, 0.0f,
		lpImage.GetID("Result/Time"), true, false);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeCnt_[static_cast<int>(StringType::Time)]);

	// •ª‚Ì•`‰æ
	DrawRotaGraph(stringPos_[static_cast<int>(StringType::Time)].x + 220,
		stringPos_[static_cast<int>(StringType::Time)].y, 1.0f, 0.0f,
		lpImage.GetDivID("Result/number")[clearTime_t], true, false);
	// •b1Œ…–Ú‚Ì•`‰æ
	DrawRotaGraph(stringPos_[static_cast<int>(StringType::Time)].x + 260,
		stringPos_[static_cast<int>(StringType::Time)].y, 1.0f, 0.0f,
		lpImage.GetDivID("Result/number")[clearTime_secf1], true, false);
	// •b2Œ…–Ú‚Ì•`‰æ
	DrawRotaGraph(stringPos_[static_cast<int>(StringType::Time)].x + 300,
		stringPos_[static_cast<int>(StringType::Time)].y, 1.0f, 0.0f,
		lpImage.GetDivID("Result/number")[clearTime_secf2], true, false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetDrawBlendMode(DX_BLENDMODE_ADD, lineAlphaval_[1]);
	DrawBox(-10, stringPos_[static_cast<int>(StringType::HitRate)].y - 30,
		box_end[1], stringPos_[static_cast<int>(StringType::HitRate)].y + 30,
		0xffffff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawRotaGraph(stringPos_[static_cast<int>(StringType::HitRate)].x,
		stringPos_[static_cast<int>(StringType::HitRate)].y, 1.0f, 0.0f,
		lpImage.GetID("Result/HitRate"), true, false);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeCnt_[static_cast<int>(StringType::HitRate)]);
	DrawRotaGraph(stringPos_[static_cast<int>(StringType::HitRate)].x + 315,
		stringPos_[static_cast<int>(StringType::HitRate)].y, 1.0f, 0.0f,
		lpImage.GetDivID("Result/number")[(int)hitRate_ / 10], true, false);
	DrawRotaGraph(stringPos_[static_cast<int>(StringType::HitRate)].x + 355,
		stringPos_[static_cast<int>(StringType::HitRate)].y, 1.0f, 0.0f,
		lpImage.GetDivID("Result/number")[(int)hitRate_ % 10], true, false);
	DrawRotaGraph(stringPos_[static_cast<int>(StringType::HitRate)].x + 395,
		stringPos_[static_cast<int>(StringType::HitRate)].y, 1.0f, 0.0f,
		lpImage.GetID("Result/percent"), true, false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetDrawBlendMode(DX_BLENDMODE_ADD, lineAlphaval_[2]);
	DrawBox(-10, stringPos_[static_cast<int>(StringType::Score)].y - 70,
		box_end[2], stringPos_[static_cast<int>(StringType::Score)].y + 70,
		0xffffff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawRotaGraph(stringPos_[static_cast<int>(StringType::Score)].x + 100,
		stringPos_[static_cast<int>(StringType::Score)].y -40, 1.0f, 0.0f,
		lpImage.GetID("Result/yourscore"), true, false);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeCnt_[static_cast<int>(StringType::Score)]);

	if (totalScore_ < 10)
	{
		DrawRotaGraph(stringPos_[static_cast<int>(StringType::Score)].x + 80,
			stringPos_[static_cast<int>(StringType::Score)].y + 40, 1.0f, 0.0f,
			lpImage.GetDivID("Result/bulletNum")[totalScore_ % 10], true, false);
	}

	if (totalScore_ >= 10 && totalScore_ < 100)
	{
		DrawRotaGraph(stringPos_[static_cast<int>(StringType::Score)].x+40,
			stringPos_[static_cast<int>(StringType::Score)].y + 40, 1.0f, 0.0f,
			lpImage.GetDivID("Result/bulletNum")[totalScore_ / 10], true, false);

		DrawRotaGraph(stringPos_[static_cast<int>(StringType::Score)].x + 80,
			stringPos_[static_cast<int>(StringType::Score)].y+40, 1.0f, 0.0f,
			lpImage.GetDivID("Result/bulletNum")[totalScore_ % 10], true, false);
	}

	if (totalScore_ >= 100 && totalScore_ < 1000)
	{
		DrawRotaGraph(stringPos_[static_cast<int>(StringType::Score)].x +40,
			stringPos_[static_cast<int>(StringType::Score)].y + 40, 1.0f, 0.0f,
			lpImage.GetDivID("Result/bulletNum")[totalScore_ / 100], true, false);

		DrawRotaGraph(stringPos_[static_cast<int>(StringType::Score)].x + 80,
			stringPos_[static_cast<int>(StringType::Score)].y, 1.0f, 0.0f,
			lpImage.GetDivID("Result/bulletNum")[totalScore_%100 / 10], true, false);

		DrawRotaGraph(stringPos_[static_cast<int>(StringType::Score)].x,
			stringPos_[static_cast<int>(StringType::Score)].y + 40, 1.0f, 0.0f,
			lpImage.GetDivID("Result/bulletNum")[totalScore_ % 100 % 10], true, false);
	}

	if (totalScore_ >= 1000 && totalScore_ < 10000)
	{
		DrawRotaGraph(stringPos_[static_cast<int>(StringType::Score)].x,
			stringPos_[static_cast<int>(StringType::Score)].y+40, 1.0f, 0.0f,
			lpImage.GetDivID("Result/bulletNum")[totalScore_ / 1000], true, false);

		DrawRotaGraph(stringPos_[static_cast<int>(StringType::Score)].x+40,
			stringPos_[static_cast<int>(StringType::Score)].y+40, 1.0f, 0.0f,
			lpImage.GetDivID("Result/bulletNum")[totalScore_ % 1000 / 100], true, false);

		DrawRotaGraph(stringPos_[static_cast<int>(StringType::Score)].x+80,
			stringPos_[static_cast<int>(StringType::Score)].y+40, 1.0f, 0.0f,
			lpImage.GetDivID("Result/bulletNum")[totalScore_ % 1000 % 100 / 10], true, false);

		DrawRotaGraph(stringPos_[static_cast<int>(StringType::Score)].x + 120,
			stringPos_[static_cast<int>(StringType::Score)].y + 40, 1.0f, 0.0f,
			lpImage.GetDivID("Result/bulletNum")[totalScore_ % 1000 % 100 % 10], true, false);
	}

	if (totalScore_ >= 10000 && totalScore_ < 100000)
	{
		DrawRotaGraph(stringPos_[static_cast<int>(StringType::Score)].x,
			stringPos_[static_cast<int>(StringType::Score)].y+40, 1.0f, 0.0f,
			lpImage.GetDivID("Result/bulletNum")[totalScore_ / 10000], true, false);

		DrawRotaGraph(stringPos_[static_cast<int>(StringType::Score)].x+40,
			stringPos_[static_cast<int>(StringType::Score)].y+40, 1.0f, 0.0f,
			lpImage.GetDivID("Result/bulletNum")[totalScore_ % 10000 / 1000], true, false);

		DrawRotaGraph(stringPos_[static_cast<int>(StringType::Score)].x+80,
			stringPos_[static_cast<int>(StringType::Score)].y+40, 1.0f, 0.0f,
			lpImage.GetDivID("Result/bulletNum")[totalScore_ % 10000 % 1000 / 100], true, false);

		DrawRotaGraph(stringPos_[static_cast<int>(StringType::Score)].x + 120,
			stringPos_[static_cast<int>(StringType::Score)].y+40, 1.0f, 0.0f,
			lpImage.GetDivID("Result/bulletNum")[totalScore_ % 10000 % 1000 % 100 / 10], true, false);

		DrawRotaGraph(stringPos_[static_cast<int>(StringType::Score)].x + 160,
			stringPos_[static_cast<int>(StringType::Score)].y+40, 1.0f, 0.0f,
			lpImage.GetDivID("Result/bulletNum")[totalScore_ % 10000 % 1000%100%10], true, false);
	}

	ScreenFlip();
}

void ResultScene::FirstUpdate(void)
{
	if (playSeFlag_[0])
	{
		lpSound.Play("Result_item", DX_PLAYTYPE_BACK);
		playSeFlag_[0] = false;
	}
	lineAlphaval_[0] += 0.8f;
	box_end[0] += 7;
	if (box_end[0] >= 810)
	{
		box_end[0] = 810;
	}
	if (lineAlphaval_[0] >= 100.0f)
	{
		lineAlphaval_[0] = 100.0f;
	}
	lpSound.ChangeVolume("Result", 255 * volPan_ / 100);
	stringPos_[static_cast<int>(strType_)].x += stringSpeed_;

	if (stringPos_[static_cast<int>(strType_)].x >= 300)
	{
		stringPos_[static_cast<int>(strType_)].x = 300;
		fadeCnt_[static_cast<int>(strType_)]+=2.0f;
	}

	if (fadeCnt_[static_cast<int>(strType_)] >= 255.0f)
	{
		fadeCnt_[static_cast<int>(strType_)] = 255.0f;
		strType_ = StringType::HitRate;
		updater_ = &ResultScene::SecondUpdate;
	}
}

void ResultScene::SecondUpdate(void)
{
	if (playSeFlag_[1])
	{
		lpSound.Play("Result_item", DX_PLAYTYPE_BACK);
		playSeFlag_[1] = false;
	}
	lineAlphaval_[1] += 0.8f;

	box_end[1] += 7;

	if (box_end[1] >= 810)
	{
		box_end[1] = 810;
	}
	if (lineAlphaval_[1] >= 100.0f)
	{
		lineAlphaval_[1] = 100.0f;
	}
	stringPos_[static_cast<int>(strType_)].x += stringSpeed_;
	percentPos_.y -= stringSpeed_;
	if (percentPos_.y <= stringPos_[static_cast<int>(strType_)].y)
	{
		percentPos_.y = stringPos_[static_cast<int>(strType_)].y;
	}

	if (fadeCnt_[static_cast<int>(strType_)] >= 255.0f)
	{
		fadeCnt_[static_cast<int>(strType_)] = 255.0f;
		strType_ = StringType::Score;
		updater_ = &ResultScene::ThirdUpdate;
	}
	if (stringPos_[static_cast<int>(strType_)].x >= 245)
	{
		fadeCnt_[static_cast<int>(strType_)]+=2.0f;
		stringPos_[static_cast<int>(strType_)].x = 245;
	}
}

void ResultScene::ThirdUpdate(void)
{
	if (playSeFlag_[2])
	{
		lpSound.Play("Result_item", DX_PLAYTYPE_BACK);
		playSeFlag_[2] = false;
	}
	lineAlphaval_[2] += 0.8f;

	box_end[2] += 7;

	if (box_end[2] >= 810)
	{
		box_end[2] = 810;
	}
	if (lineAlphaval_[2] >= 100.0f)
	{
		lineAlphaval_[2] = 100.0f;
	}
	stringPos_[static_cast<int>(strType_)].x += stringSpeed_;

	if (fadeCnt_[static_cast<int>(strType_)] >= 255.0f)
	{
		fadeCnt_[static_cast<int>(strType_)] = 255.0f;
		strType_ = StringType::PushB;
		updater_ = &ResultScene::FinalUpdate;
	}
	if (stringPos_[static_cast<int>(strType_)].x >= 300)
	{
		fadeCnt_[static_cast<int>(strType_)] += 2.0f;
		stringPos_[static_cast<int>(strType_)].x = 300;
	}
}

void ResultScene::FinalUpdate(void)
{
	volPan_ += 0.3f;
	if (volPan_ >= 255.0f)
	{
		volPan_ = 255.0f;
	}
	lpSound.ChangeVolume("Result", 255 * volPan_ / 100);
	fadeCnt_[static_cast<int>(strType_)] += 0.5f;

	if (fadeCnt_[static_cast<int>(strType_)] >= 255.0f)
	{
		fadeCnt_[static_cast<int>(strType_)] = 255.0f;
	}
	if (stringPos_[static_cast<int>(strType_)].x >= 200)
	{
		stringPos_[static_cast<int>(strType_)].x = 200;
	}
}
