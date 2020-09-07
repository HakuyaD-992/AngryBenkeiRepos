#pragma once
#include "Object.h"

constexpr int floorX = 800;
constexpr int floorY = 0;
constexpr int floorZ = 320;

class Floor :
	public Object
{
public:
	Floor(Vector2I pos, ObjectType type);
	~Floor();

	// èâä˙âª
	bool Initialize(void);
	const Vector2I& GetPos(void);
	void Draw(void);
private:

};

