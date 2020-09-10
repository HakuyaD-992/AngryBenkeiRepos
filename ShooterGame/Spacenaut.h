#pragma once
#include "Enemy.h"
class Spacenaut :
	public Enemy
{
public:
	Spacenaut(Vector2I pos, int z, ActorType type,
		std::vector<std::shared_ptr<ControlledPlayer>>& player);
	~Spacenaut();

	void UpDate(void);
	void Draw_(void);

private:

};

