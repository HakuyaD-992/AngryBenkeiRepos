#pragma once
#include "Enemy.h"
class Pod :
	public Enemy
{
public:
	Pod(Vector2I pos, int z,ActorType type,
		std::vector<std::shared_ptr<ControlledPlayer>>& player);
	~Pod();

	void UpDate(void);
	void Draw_(void);

private:

};

