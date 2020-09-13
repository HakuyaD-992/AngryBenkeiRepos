#pragma once
#include "BulletBase.h"
#include "ActorType.h"
class EnemyBullet :
	public BulletBase
{
public:
	EnemyBullet(Vector2I pos, int z,const ActorType& actor, bool isLeft);
	~EnemyBullet();

	void UpDate(void);
	void Draw(void);
	bool Initialize(void);
	void UpDateAnimation(std::string animName);

private:
	// 発射した弾の順番を表す番号
	static int no_;
	int bulletNo_;

	bool isMove_;
	bool extendFlag_;
};

