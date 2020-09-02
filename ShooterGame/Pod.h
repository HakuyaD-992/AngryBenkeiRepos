#pragma once
#include "Enemy.h"
class Pod :
	public Enemy
{
public:
	Pod(Vector2I pos, int z,ActorType type,
		std::list<std::shared_ptr<ControlledPlayer>>& player);
	~Pod();

	void UpDate(void);
	void Draw_(void);

	void(Pod::* updater_)(void);

private:

	// 初期行動
	void Walk(void);
	// ﾌﾟﾚｲﾔｰとのZ軸を合わせる
	void Z_Arrangement(void);
	// ﾌﾟﾚｲﾔｰとのZ軸があったら攻撃
	void Attack(void);
	// ﾌﾟﾚｲﾔｰとのZ軸をずらす(攻撃回避)
	void Evacuate(void);


};

