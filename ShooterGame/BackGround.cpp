#include <DxLib.h>
#include "BackGround.h"

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
	return false;
}

void BackGround::Draw(void)
{
	DrawRotaGraph(pos_.x, pos_.y - 24, exRate_, rotRate_, imageHandle_, true, false);

}
