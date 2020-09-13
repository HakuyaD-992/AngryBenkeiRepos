#include <DxLib.h>
#include "ScreenEffectMng.h"
#include "ImageManager.h"
#include "BackGround.h"

void BackGround::Draw(void)
{
<<<<<<< HEAD
	DrawRotaGraph(pos_.x, pos_.y - 24 + lpS_Effect.MoveAmountCalculator(type_,player_).y, exRate_, rotRate_, imageHandle_, true, false);
}

BackGround::BackGround(std::shared_ptr<ControlledPlayer>& player):
=======
	for (auto itr : player_)
	{
		DrawRotaGraph(pos_.x, pos_.y - 24 + lpS_Effect.MoveAmountCalculator(type_, itr).y, exRate_, rotRate_, imageHandle_, true, false);
	}
}

BackGround::BackGround(std::vector<std::shared_ptr<ControlledPlayer>>& player) :
>>>>>>> 56ac109e597b0e82e8d13a0ad1b670f3c322930f
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

	Object::Initialize();
	return true;
}
