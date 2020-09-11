#include <DxLib.h>
#include "Floor.h"
#include "ControlledPlayer.h"
#include "ScreenEffectMng.h"

Floor::Floor(Vector2I pos, ObjectType type, std::vector<std::shared_ptr<ControlledPlayer>>& player):
	Object(player)
{
	pos_ = pos;
	type_ = type;
	Initialize();
}

Floor::~Floor()
{
}

bool Floor::Initialize(void)
{
	name_ = "Floor";
	Object::Initialize();
	return true;
}

const Vector2I& Floor::GetPos(void)
{
	return pos_;
}

void Floor::Draw(void)
{
	lpS_Effect.DrawRotaGraph(Vector2F(pos_.x, pos_.y + 30.0f), exRate_, rotRate_, imageHandle_, true, false);
}
