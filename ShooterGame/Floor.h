#pragma once
#include "Object.h"
class Floor :
	public Object
{
public:
	Floor(Vector2I pos, ObjectType type);
	~Floor();

	// ‰Šú‰»
	bool Initialize(void);

private:

};

