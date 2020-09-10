#pragma once
#include <vector>
#include "AIBase.h"

#include "Geometory.h"

constexpr int LaserSizeX = 0;
constexpr int LaserSizeY = 50;

class BigboyAI :
	public AIBase
{
public:
	BigboyAI(Enemy& enemy);
	~BigboyAI();

	void Update(std::list<std::shared_ptr<Enemy>>& enemies);
private:
	void Initialize(void);
	// 関数ﾎﾟｲﾝﾀ
	bool(BigboyAI::* updater_)(std::list<std::shared_ptr<Enemy>>& enemies);

	// 一定時間止まってﾌﾟﾚｲﾔｰの行動を観察する。
	// ここでBigboyの行動を決定する。
	bool Observe(std::list<std::shared_ptr<Enemy>>& enemies);
	// ﾌﾟﾚｲﾔｰに向かって歩く
	bool Walk(std::list<std::shared_ptr<Enemy>>& enemies);
	// ﾌﾟﾚｲﾔｰとのZ軸を合わせる
	bool ZArrange(std::list<std::shared_ptr<Enemy>>& enemies);
	// ﾌﾚｰﾑ単位で攻撃する
	bool Attack(std::list<std::shared_ptr<Enemy>>& enemies);
	// 一定時間経ったら高くｼﾞｬﾝﾌﾟする
	bool Jump(std::list<std::shared_ptr<Enemy>>& enemies);
	// ﾀﾞﾒｰｼﾞ
	bool OnDamaged(std::list<std::shared_ptr<Enemy>>& enemies);
	// 死ぬ
	bool Death(std::list<std::shared_ptr<Enemy>>& enemies);
	// タックル
	bool LaserAttack(std::list<std::shared_ptr<Enemy>>& enemies);

	float jumpSp_;
	float jumpForce_;
	float jumpFirstSp_;

	float tackleAccelSp_;
	float tackleSp_;
	float tackleFirstSp_;

	bool isShotLaser_[2];

	int walkFrame_;
	bool isJumpAction_;
	int jumpInterval_;

	Vector2I laserRect_;
};

