#pragma once
#include <type_traits>

enum class ObjectType
{
	Floor,
	BackGround,
	Max
};

static ObjectType begin(ObjectType)
{
	return ObjectType::Floor;
}

static ObjectType end(ObjectType)
{
	return ObjectType::Max;
}

static ObjectType operator++(ObjectType& obj)
{
	return (obj = (ObjectType)(std::underlying_type<ObjectType>::type(obj) + 1));
}

static ObjectType operator*(ObjectType& obj)
{
	return obj;
}