#include <DxLib.h>

#include "KeyInput.h"
#include "PadInput.h"
#include "Application.h"
#include "SceneController.h"
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
