#include "Gravity.h"

Gravity::Gravity(void)
{
	gPower = 0.0f;
}

Gravity::~Gravity()
{
}

void Gravity::PutGravityOnActor(Vector2 & pos)
{
	// �d�͉��Z
	gPower += GRAVITY;
	// ���̂��߼޼�ݎ��Ԃɏd�͂�������
	pos.y += gPower;
}
