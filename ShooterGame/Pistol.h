#pragma once
#include "WeaponBase.h"
class Pistol :
	public WeaponBase
{
public:
	Pistol(Vector2I pos, int z, WeaponType type);
	~Pistol();

	void UpDateAnimation(std::string animName);
	void UpDate(void);
private:
	float reloadCnt_;
};

