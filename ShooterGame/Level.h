#pragma once
#include <type_traits>

enum Level
{
	Lv_1,
	Lv_2,
	Lv_3,
	Max
};

static Level begin(Level)
{
	return Level::Lv_1;
}

static Level end(Level)
{
	return Level::Max;
}

static Level operator++(Level& type)
{
	return (type = (Level)(std::underlying_type<Level>::type(type) + 1));
}

static Level operator+(Level type, int i)
{
	return Level(int(type) + i);
}

static Level operator*(Level& type)
{
	return type;
}

