#include <DxLib.h>
#include "Floor.h"

Floor::Floor(Vector2I pos, ObjectType type)
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

void Floor::Draw(void)
{
	DrawRotaGraph(pos_.x, pos_.y + 30, exRate_, rotRate_, imageHandle_, true, false);
}
