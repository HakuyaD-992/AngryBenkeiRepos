#pragma once
#include <memory>
#include <string>
#include "BulletBase.h"
#include "ActorType.h"
#include "Level.h"

class Enemy;

class EnemyBullet :
	public BulletBase
{
public:
	EnemyBullet(Vector2I pos, int z,const ActorType& actor,
		bool isLeft,Enemy& enemy);
	~EnemyBullet();

	void UpDate(void);
	void Draw(void);
	void UpDateAnimation(std::string animName);

private:
	// î≠éÀÇµÇΩíeÇÃèáî‘Çï\Ç∑î‘çÜ
	static int no_;
	int bulletNo_;

	bool isMove_;
	bool extendFlag_;
	float bulletExplosionCnt_;

	Level level_;

	Enemy& enemy_;

};

