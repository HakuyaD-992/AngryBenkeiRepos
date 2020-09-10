#include "TitleScene.h"
#include "PlayScene.h"
#include "PLAYER.h"
#include "Input.h"
#include "Application.h"
#include "ImageManager.h"
#include "EffectManager.h"
#include "SceneController.h"
#include "SoundManager.h"


TitleScene::TitleScene(SceneController& sCon):
	BaseScene(sCon)
{
	Initialize();
	lpSound.Play("title",DX_PLAYTYPE_LOOP);
}

TitleScene::~TitleScene()
{
}

void TitleScene::UpDate(const std::vector<std::shared_ptr<Input>>& input)
{
	auto inputData1_ = input[static_cast<int>(PLAYER::ONE)]->GetPeriData();

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
		lpSound.Play("fadein",DX_PLAYTYPE_BACK);
		pushFadeCnt_++;
		if (pushFadeCnt_ >= 255)
		{
			pushFadeCnt_ = 255;
		}
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
					lpSound.Play("cursorMove",DX_PLAYTYPE_BACK);
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
					lpSound.Play("cursorMove",DX_PLAYTYPE_BACK);
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
					lpSound.Play("start",DX_PLAYTYPE_BACK);
					lpEffect.Play("thunder", Vector2I(arrowPos_.x + 120, arrowPos_.y + 120));
					isNext_ = true;
				}
			}
		}
	}
	if (isNext_)
	{
		// ｹﾞｰﾑｽﾀｰﾄ
		if (nextFlag_ == Next::Game && (lpEffect.IsPlayingEffect("thunder") == -1))
		{
			lpSound.Stop("title");
			sceneCtl_.ChangeScene(std::make_shared<PlayScene>(sceneCtl_));
		}
	}


	// 2P参戦
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

	//int Pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);        //入力状態をPadに格納
	//for (int i = 0; i < 28; i++) {      //ボタン28個分ループ
	//	if (Pad & (1 << i)) {             //ボタンiの入力フラグが立っていたら
	//		DrawFormatString(0, i * 15, GetColor(255, 255, 255), "%dのキーが押されています", i);
	//	}
	//}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeCnt_);
	DrawGraph(stringPos_.x, stringPos_.y, lpImage.GetID("Title/title"), true);
	DrawGraph(arrowPos_.x, arrowPos_.y + stringSp_[0].y, lpImage.GetID("Title/arrow"), true);

	DrawGraph(stringPos_.x + 50, stringPos_.y + stringSp_[0].y, lpImage.GetID("Title/start"), true);
	DrawGraph(stringPos_.x + 50, stringPos_.y + stringSp_[1].y, lpImage.GetID("Title/manual"), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, pushFadeCnt_);
	DrawGraph(stringPos_.x - 180, stringPos_.y + stringSp_[1].y + 100, lpImage.GetID("Title/push"), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	lpEffect.Draw();

	ScreenFlip();
}

void TitleScene::Initialize(void)
{
	auto& app = Application::Instance();

	stringPos_ = { app.GetViewport().GetSize().x / 2, app.GetViewport().GetSize().y / 2 - 100 };
	// 矢印のﾎﾟｼﾞｼｮﾝ
	arrowPos_ = { stringPos_.x - 20,stringPos_.y };

	nextFlag_ = Next::Game;
	isNext_ = false;

	// 画像のﾛｰﾄﾞ
	lpImage.Load("Title/title");
	lpImage.Load("Title/start");
	lpImage.Load("Title/manual");
	lpImage.Load("Title/arrow");
	lpImage.Load("Title/push");

	lpSound.Load("cursorMove", true);
	lpSound.Load("title", true);
	lpSound.Load("start", false);
	lpSound.Load("fadein", false);

	// ｴﾌｪｸﾄのﾛｰﾄﾞ
	lpEffect.Load("thunder");

	for (int i = 0; i < 2; i++)
	{
		stringSp_[i] = { 1,1 };
	}

	// ﾌｪｰﾄﾞｶｳﾝﾄの初期化
	fadeCnt_ = 0;
	pushFadeCnt_ = 0;
	fade_ = Fade::In;
	//return true;
}

