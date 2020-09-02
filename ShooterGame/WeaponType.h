#pragma once
#include <type_traits>

enum class WeaponType
{
	Pistol,
	ShotGun,
	SubMachineGun,
	Max
};

static WeaponType begin(WeaponType)
{
	return WeaponType::Pistol;
}

static WeaponType end(WeaponType)
{
	return WeaponType::Max;
}

static WeaponType operator++(WeaponType& obj)
{
	return (obj = (WeaponType)(std::underlying_type<WeaponType>::type(obj) + 1));
}

static WeaponType operator*(WeaponType& obj)
{
	return obj;
}
