#pragma once
#include <map>
#include "Geometory.h"
#include "Enemy.h"

using namespace std;
class Exoskeleton :
	public Enemy
{
public:
	Exoskeleton(Vector2I pos,int z,ActorType type,
		std::vector<std::shared_ptr<ControlledPlayer>>& player);
	~Exoskeleton();

	void UpDate(void);
	void Draw_(void);

	void (Exoskeleton::* updater)(void);

private:
	// 走る
	void Run(void);
	// ﾌﾟﾚｲﾔｰのZ軸に自分のZ軸を合わせる
	void ArrangementZ(void);
	// Z軸がﾌﾟﾚｲﾔｰとあったら攻撃をする(弾を出す)
	void Attack(void);
	// 弾が無くなれば一旦退避
	void Evacuation(void);
	// 弾の補充
	void RefillBullet(void);

	int frame;

	vector<pair<Vector2F, int>> afterimage_limit;
};

