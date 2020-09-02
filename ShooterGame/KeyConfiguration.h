#pragma once
#include <type_traits>

// 无垒偺庬椶
enum class KeyConfiguration
{
	Right,
	Left,
	Up,
	Down,
	// 峌寕无垒
	Fire,
	// 晲婍曄峏无垒
	ChangeWeapon,
	// 刿澳迌{僞儞
	Reload,
	// 嫁踢无垒
	Jump,
	// 寛掕
	Decision,
	// 鼐
	Reset,
	Max
};

static KeyConfiguration begin(KeyConfiguration)
{
	return KeyConfiguration::Right;
}

static KeyConfiguration end(KeyConfiguration)
{
	return KeyConfiguration::Max;
}

static KeyConfiguration operator++(KeyConfiguration& config)
{
	return (config =
		KeyConfiguration(std::underlying_type<KeyConfiguration>::type(config) + 1));
}

static KeyConfiguration operator*(KeyConfiguration config)
{
	return config;
}

