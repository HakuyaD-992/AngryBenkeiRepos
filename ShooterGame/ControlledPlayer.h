#pragma once
#include <list>

#include "Actor.h"
#include "PLAYER.h"

//class Enemy;
class WeaponBase;

class ControlledPlayer :
	public Actor
{
public:
	ControlledPlayer(Vector2I pos, int z, const ActorType& type/*, std::list<std::shared_ptr<Enemy>>& enemyList*/);
	~ControlledPlayer();

	void UpDate(void);

	const std::shared_ptr<WeaponBase>& GetCurrentWeapon(void)
	{
		return currentWeapon_;
	}

	void Draw_(void);

private:
	// 何PなのかをActorｸﾗｽで知れるようにするためにここに記入
	static int player_;
	// 今何Pなのかの情報
	PLAYER playerNo_ = PLAYER::MAX;

	bool Initialize(void);
	void Walk(const Vector2I& speed, const int& zSp);
	void Jump(void);
	void Fire(void);

	// ﾌﾟﾚｲﾔｰの行動に関する関数ﾎﾟｲﾝﾀ
	void(ControlledPlayer::* updater_)(void);
	// 敵のﾘｽﾄ
	//std::list<std::shared_ptr<Enemy>>& enemies_;
	std::vector<std::shared_ptr<WeaponBase>> weapons_;
	std::shared_ptr<WeaponBase> currentWeapon_;

	// 今現在装備している武器をlistから引っ張ってきたいので
	// 現在装備している武器ナンバー
	int currentWeaponNo_;

	// 武器をﾌﾟﾚｲﾔｰの手元に合わせるための調整用変数
	Vector2I weaponsArrangementAmount_;
};

