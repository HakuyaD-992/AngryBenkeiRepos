#pragma once
#include <mutex>
#include "Vector2.h"

// ��������d��
#define GRAVITY 0.3f

class Gravity
{
public:
	Gravity(void);
	~Gravity();

	// ���̂ɑ΂��ďd�͂�������֐�
	void PutGravityOnActor(Vector2& pos);

private:
	// ���̂ɑ΂��Ă�����d��
	float gPower;
};

