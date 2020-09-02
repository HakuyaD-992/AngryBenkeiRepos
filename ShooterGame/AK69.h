#pragma once
#include "WeaponBase.h"
class AK69 :
	public WeaponBase
{
public:
	AK69(Vector2I pos, int z, WeaponType type);
	~AK69();
	void UpDate(void);
	void UpDateAnimation(std::string animName);
private:

};

