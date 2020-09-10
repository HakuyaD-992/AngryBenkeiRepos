#pragma once
#include <type_traits>

enum class ActorType
{
	Player,
	Pod,
	Exoskeleton,
	Spacenaut,
	Bigboy,
	Max
};

static ActorType begin(ActorType)
{
	return ActorType::Player;
}

static ActorType end(ActorType)
{
	return ActorType::Max;
}

static ActorType operator++(ActorType& type)
{
	return (type = (ActorType)(std::underlying_type<ActorType>::type(type) + 1));
}

static ActorType operator+(ActorType type,int i)
{
	return ActorType(int(type) + i);
}

static ActorType operator*(ActorType& type)
{
	return type;
}