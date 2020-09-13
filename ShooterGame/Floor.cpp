#include <DxLib.h>
#include "Floor.h"
#include "ControlledPlayer.h"
#include "ScreenEffectMng.h"

<<<<<<< HEAD
Floor::Floor(Vector2I pos, ObjectType type, std::shared_ptr<ControlledPlayer>& player):
=======
Floor::Floor(Vector2I pos, ObjectType type, std::vector<std::shared_ptr<ControlledPlayer>>& player):
>>>>>>> 56ac109e597b0e82e8d13a0ad1b670f3c322930f
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
