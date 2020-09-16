#include <DxLib.h>
#include "ScreenEffectMng.h"
#include "ImageManager.h"
#include "BackGround.h"

void BackGround::Draw(void)
{
	DrawRotaGraph(pos_.x, pos_.y - 24 + lpS_Effect.MoveAmountCalculator(type_,player_).y, exRate_, rotRate_, imageHandle_, true, false);
	scoreUIPos_ = pos_;
	DrawRotaGraph(scoreUIPos_.x + 50, scoreUIPos_.y - 24 + lpS_Effect.MoveAmountCalculator(type_, player_).y,
		1.0f, 0.0f,
		lpImage.GetID("UI/Score"), true, false);
}

BackGround::BackGround(std::shared_ptr<ControlledPlayer>& player):
	Object(player)
{
	Initialize();
}

BackGround::~BackGround()
{
}

bool BackGround::Initialize(void)
{
	name_ = "Background";
	type_ = ObjectType::BackGround;
	scoreUIPos_ = pos_;

	Object::Initialize();
	return true;
}
