#pragma once
#include <memory>
#include "Object.h"

constexpr int floorX = 800;
constexpr int floorY = 0;
constexpr int floorZ = 320;

class Floor :
	public Object
{
public:
<<<<<<< HEAD
	Floor(Vector2I pos, ObjectType type, std::shared_ptr<ControlledPlayer>& player);
=======
	Floor(Vector2I pos, ObjectType type, std::vector<std::shared_ptr<ControlledPlayer>>& player);
>>>>>>> 56ac109e597b0e82e8d13a0ad1b670f3c322930f
	~Floor();

	// èâä˙âª
	bool Initialize(void);
	const Vector2I& GetPos(void);
	void Draw(void);
private:

};

