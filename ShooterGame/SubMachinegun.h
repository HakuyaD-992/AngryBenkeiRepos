#pragma once
#include "WeaponBase.h"
class SubMachinegun :
	public WeaponBase
{
public:
	SubMachinegun(Vector2I pos, int z, WeaponType type);
	~SubMachinegun();

	void UpDate(void);

	void UpDateAnimation(std::string animName);
private:

};

