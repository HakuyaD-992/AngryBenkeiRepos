#pragma once
#include "BulletBase.h"
#include "WeaponBase.h"


class PlayerBullet :
	public BulletBase
{
public:
	PlayerBullet(Vector2I pos,int z,WeaponType weapon,bool isLeft);
	~PlayerBullet();

	void UpDate(void);
	void Draw(void);
	void UpDateAnimation(std::string animName);

private:
	
};

