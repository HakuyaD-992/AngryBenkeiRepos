#pragma once
#include <memory>
#include <list>
#include "Actor.h"

class ControlledPlayer;

class Enemy :
	public Actor
{
public:
	Enemy(std::list<std::shared_ptr<ControlledPlayer>>& player);
	~Enemy();

	virtual void UpDate(void) = 0;
	virtual void Draw_(void) = 0;
	virtual bool Initialize(void);
	virtual void SetPos(const Vector2I& pos, int z);

private:

protected:
	std::list<std::shared_ptr<ControlledPlayer>>& player_;
	
};

