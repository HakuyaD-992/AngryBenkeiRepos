#pragma once
#include "AIBase.h"
class ExoskeletonAI :
    public AIBase
{
public:
	ExoskeletonAI(Enemy& enemy);
	~ExoskeletonAI();

	void Update(std::list<std::shared_ptr<Enemy>>& enemies);

	// ﾌﾟﾚｲﾔｰの背後に回り込む
	bool Run(std::list<std::shared_ptr<Enemy>>& enemies);
	// 死ぬ
	bool Death(std::list<std::shared_ptr<Enemy>>& enemies);
private:

	void Initialize(void);
	bool(ExoskeletonAI::* updater_)(std::list<std::shared_ptr<Enemy>>&);

	int frame;
	float rad;	//ラジアン角度
	Vector2I player_pos;
};

