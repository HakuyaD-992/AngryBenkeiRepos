#pragma once
#include "Enemy.h"
class Bigboy :
	public Enemy
{
public:
	Bigboy(Vector2I pos, int z, ActorType type,
		std::vector<std::shared_ptr<ControlledPlayer>>& player);
	~Bigboy();

	void UpDate(void);
	void Draw_(void);

private:




};

