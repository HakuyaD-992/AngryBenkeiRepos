#pragma once
#include "Vector2.h"
#include"DIRECTION.h"

#define AccelFirstSpeed 10.0f
#define Size_X 68
#define Size_Y 9

class Shot
{
public:
	Shot(Vector2 pos,DIRECTION direction);
	~Shot();

	void Action(void);

	const Vector2& GetPos(void) const
	{
		return pos;
	}

	const Vector2& GetSize(void) const
	{
		return size;
	}

	const bool& GetDeleteflag(void) const
	{
		return deleteFlag;
	}

	void Delete(void)
	{
		deleteFlag = true;
	}
	void Draw(void);

private:
	bool Init(void);



	Vector2 pos;
	Vector2 size;
	DIRECTION direction;
	int animCount;

	float accel;
	float firstSpeed;
	float accelSpeed;

	bool deleteFlag;



};

