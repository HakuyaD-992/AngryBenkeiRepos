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

const Vector2I& Floor::GetPos(void)
{
	return pos_;
}
