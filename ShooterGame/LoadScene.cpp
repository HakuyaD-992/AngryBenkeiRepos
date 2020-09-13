#include <DxLib.h>

#include "LoadScene.h"
#include "TitleScene.h"
#include "ImageManager.h"
#include "Application.h"
#include "SoundManager.h"
#include "SceneController.h"

LoadScene::LoadScene(SceneController& sCon):
	BaseScene(sCon)
{
	Initialize();
	updater_ = &LoadScene::NowLoading;
}

LoadScene::~LoadScene()
{
	loadSize_ = 0;
}

void LoadScene::UpDate(const std::vector<std::shared_ptr<Input>>& input)
{
	// Û°ÄÞ‚Ì’†g‚ÌXV
	(this->*updater_)();
}

void LoadScene::Initialize(void)
{
	loadTime_ = 0;
	loadCnt_ = 0;
	standbyCnt_ = 0;
	standbyFlag_ = false;

	exRate_ = 0.0f;

	LoadImageResources();
}

void LoadScene::Draw(void)
{
	auto& app = Application::Instance();

	ClearDrawScreen();

	DrawRotaGraph(app.GetViewport().GetSize().x / 2, 100, 1.0f, 0.0f,
		lpImage.GetID("Title/instructions"), true, false);
	DrawRotaGraph(app.GetViewport().GetSize().x / 2, 200, 1.0f, 0.0f,
		lpImage.GetID("Title/instructions2"), true, false);

	DrawRotaGraph(app.GetViewport().GetSize().x / 2, 295, 1.0f, 0.0f,
		lpImage.GetID("Title/Nowloading"), true, false);

	DrawBox(app.GetViewport().GetSize().x / 2 - 75, 323,
		app.GetViewport().GetSize().x / 2 - 75 + (loadCnt_ * 50), 347, 0x00ff00, true);

	DrawRotaGraph(app.GetViewport().GetSize().x / 2, 335, 1.0f, 0.0f,
		lpImage.GetID("Title/NowloadingGauge"), true, false);

	DrawRotaGraph(app.GetViewport().GetSize().x / 2,
		330, exRate_, 0.0f,
		lpImage.GetID("Title/ready"),
		true, false);

	DrawRotaGraph(app.GetViewport().GetSize().x / 2, 420, 1.0f, 0.0f,
		lpImage.GetID("UI/Enemies"), true, false);
	DrawRotaGraph(app.GetViewport().GetSize().x / 2 - 200, 500, 1.0f, 0.0f,
		lpImage.GetID("UI/Pod_UI"), true, false);
	DrawRotaGraph(app.GetViewport().GetSize().x / 2, 500, 1.0f, 0.0f,
		lpImage.GetID("UI/Exoskeleton_UI"), true, false);
	DrawRotaGraph(app.GetViewport().GetSize().x / 2 + 200, 500, 1.0f, 0.0f,
		lpImage.GetID("UI/Spacenaut_UI"), true, false);
	ScreenFlip();
}

void LoadScene::NowLoading(void)
{
	loadCnt_++;

	lpSound.Load("bgm_wave" + std::to_string(loadCnt_), true);

	if (loadCnt_ >= loadSize_)
	{
		standbyFlag_ = true;
		LoadSoundResources();
		lpSound.Play("ready", DX_PLAYTYPE_BACK);
		updater_ = &LoadScene::Standby;
	}
}

void LoadScene::Standby(void)
{
	standbyCnt_++;
	exRate_ += 0.1f;
	if (exRate_ >= 1.0f)
	{
		exRate_ = 1.0f;
	}
	if (standbyCnt_ >= 100)
	{
		updater_ = &LoadScene::StartNext;
	}
}

void LoadScene::StartNext(void)
{
	sceneCtl_.ChangeScene(std::make_shared<TitleScene>(sceneCtl_));
}

void LoadScene::LoadSoundResources(void)
{
	lpSound.Load("cursorMove", true);
	lpSound.Load("start", true);
	lpSound.Load("fadein", true);
	lpSound.Load("ready", true);

	lpSound.Load("pistol/fire", true);
	lpSound.Load("sub_machinegun/fire", true);
	lpSound.Load("shotgun/fire", true);

	lpSound.Load("Pod/fire", true);
	lpSound.Load("Bigboy/charge", true);
	lpSound.Load("Spacenaut/fire", true);
	lpSound.Load("Bigboy/fire", true);

	lpSound.Load("damage", true);

	lpSound.Load("pistol/get", true);
	lpSound.Load("sub_machinegun/get", true);
	lpSound.Load("shotgun/get", true);

	lpSound.Load("explosion", true);
	lpSound.Load("explosionboss", true);
	lpSound.Load("bgm", true);
	lpSound.Load("onFloor", true);
}

void LoadScene::LoadImageResources(void)
{
	// ‰æ‘œ‚ÌÛ°ÄÞ
	lpImage.Load("Title/title");
	lpImage.Load("Title/start");
	lpImage.Load("Title/manual");
	lpImage.Load("Title/arrow");
	lpImage.Load("Title/push");
	lpImage.Load("Title/instructions");
	lpImage.Load("Title/instructions2");
	lpImage.Load("Title/Nowloading");
	lpImage.Load("Title/NowloadingGauge");
	lpImage.Load("Title/ready");

	lpImage.Load("UI/Enemies");
	lpImage.Load("UI/Pod_UI");
	lpImage.Load("UI/Exoskeleton_UI");
	lpImage.Load("UI/Spacenaut_UI");

	lpImage.LoadDiv("Normalsky", Vector2I(800, 387), Vector2I(2, 3));
	lpImage.LoadDiv("Thundersky", Vector2I(800, 387), Vector2I(2, 3));
	lpImage.LoadDiv("UI/wave_num", Vector2I(60, 60), Vector2I(3, 1));
	lpImage.LoadDiv("UI/number", Vector2I(22, 40), Vector2I(10, 1));
	lpImage.LoadDiv("Item/items", Vector2I(32, 32), Vector2I(3, 1));

	lpImage.Load("UI/wave");
	lpImage.Load("UI/untilnext");
	lpImage.Load("UI/bullets");

}
