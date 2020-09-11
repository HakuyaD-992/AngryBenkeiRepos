#include <DxLib.h>

#include "KeyInput.h"
#include "PadInput.h"
#include "Application.h"
#include "SceneController.h"
#include "ImageManager.h"
#include "SoundManager.h"
#include "EffectManager.h"
#include "TitleScene.h"


namespace
{
	Rect w_size_(0, 0, 800, 600);
}

Vector2I Viewport::GetSize() const
{
	Vector2I ret = { w_size_.w,w_size_.h };
	return ret;
}

bool Application::Initialize(void)
{
	SetGraphMode(w_size_.w, w_size_.h, 32);
	ChangeWindowMode(true);
	if (DxLib_Init() == -1)
	{
		return false;
	}
	// EffectÇÃèâä˙âª
	// ¥Ã™∏º±égóp
	lpEffect.Init(Vector2I(w_size_.w, w_size_.h));
	SetDrawScreen(DX_SCREEN_BACK);
	sceneCtl_ = std::make_shared<SceneController>();
	sceneCtl_->PushScene(std::make_shared<TitleScene>(*sceneCtl_));

	input_.emplace_back(std::make_shared<KeyInput>());
	//input_.emplace_back(std::make_shared<KeyInput>());
	// 1P controller
	input_[static_cast<int>(PLAYER::ONE)]->Setup(PLAYER::ONE);
	// 2P controller
	//input_[static_cast<int>(PLAYER::TWO)]->Setup(PLAYER::TWO);

	auto& imageMng = ImageManager::GetInstance();

	imageMng.LoadDiv("Normalsky", Vector2I(800, 387), Vector2I(2, 3));
	imageMng.LoadDiv("Thundersky", Vector2I(800, 387), Vector2I(2, 3));
	imageMng.LoadDiv("UI/wave_num", Vector2I(60, 60), Vector2I(3, 1));
	imageMng.LoadDiv("UI/number", Vector2I(22, 40), Vector2I(10, 1));
	imageMng.LoadDiv("Item/items", Vector2I(32, 32), Vector2I(3, 1));

	imageMng.Load("UI/enemy1_UI2");
	imageMng.Load("UI/wave");
	imageMng.Load("UI/untilnext");
	imageMng.Load("UI/bullets");

	lpSound.Load("pistol/fire", true);
	lpSound.Load("sub_machinegun/fire", true);
	lpSound.Load("shotgun/fire", true);

	lpSound.Load("Pod/fire", true);
	lpSound.Load("Spacenaut/fire", true);
	lpSound.Load("Bigboy/fire", true);


	lpSound.Load("damage", true);

	lpSound.Load("pistol/get", true);
	lpSound.Load("sub_machinegun/get", true);
	lpSound.Load("shotgun/get", true);

	lpSound.Load("explosion", true);
	lpSound.Load("bgm", true);
	lpSound.Load("onFloor", true);

	for (int i = 0; i < static_cast<int>(Wave::Max); i++)
	{
		lpSound.Load("bgm_wave" + std::to_string(i + 1), true);
	}

	return true;
}

void Application::Exit(void)
{
	isExit_ = true;
}

void Application::Run(void)
{
	while (!CheckHitKey(KEY_INPUT_ESCAPE))
	{
		for (auto&& in : input_)
		{
			(*in)();
		}

		sceneCtl_->UpdateScene(input_);
	}
}

void Application::Terminate(void)
{
	DxLib_End();
}

const Viewport& Application::GetViewport(void) const
{
	return viewport_;
}

std::shared_ptr<Input>& Application::GetInput(const PLAYER& player)
{
	return input_[static_cast<int>(player)];
}
