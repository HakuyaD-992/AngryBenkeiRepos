#pragma once
#include <list>
#include <array>

#include "Actor.h"
#include "PLAYER.h"
#include "MoneyType.h"

class Enemy;
class WeaponBase;
class Item;
class MoneyItem;

class ControlledPlayer :
	public Actor
{
public:
	ControlledPlayer(Vector2I pos, int z, const ActorType& type,
		std::list<std::shared_ptr<Item>>& itemList/*,
		std::list<std::shared_ptr<MoneyItem>>& moneyList*/);
	~ControlledPlayer();

	void UpDate(void);

	const std::shared_ptr<WeaponBase>& GetCurrentWeapon(void)
	{
		return currentWeapon_;
	}

	virtual bool& GetisOnFloor(void)
	{
		return isOnFloor_;
	}

	virtual bool& GetisHitEnemyZ(void)
	{
		return isHitEnemyZ_;
	}

	virtual int& GetUseBullet(void)
	{
		return use_Bullet;
	}

	const std::vector<std::shared_ptr<WeaponBase>>& GetWeapons(void)
	{
		return weapons_;
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
	// ｱｲﾃﾑ取得
	void GetItems(void);
	// お金取得
	//void GetMoneys(void);

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

	// 床の可動範囲にﾌﾟﾚｲﾔｰがいるかのﾌﾗｸﾞ
	bool isOnFloor_;
	Vector2I weaponsUIPos_;

	Vector2I bulletNumPos_;

	// 加算値
	int addBlendval_;
	bool addBlendFlag_;

	// 使用した銃弾の数
	int use_Bullet;

	bool isHitEnemyZ_;

	std::array<int,static_cast<int>(MoneyType::Max)> havingMoney_;

	std::list<std::shared_ptr<Item>>& items_;
	//std::list<std::shared_ptr<MoneyItem>>& moneyItems_;

	std::list<std::pair<std::pair<Vector2I,int>,int>> getBulletNumPos_;


};

