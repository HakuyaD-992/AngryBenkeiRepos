#include <DxLib.h>
#include "ScreenEffectMng.h"
#include "ImageManager.h"
#include "BackGround.h"

void BackGround::Draw(void)
{
	DrawRotaGraph(pos_.x, pos_.y - 24 + lpS_Effect.MoveAmountCalculator(type_).y, exRate_, rotRate_, imageHandle_, true, false);
}

BackGround::BackGround()
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

	Object::Initialize();
	return true;
}
