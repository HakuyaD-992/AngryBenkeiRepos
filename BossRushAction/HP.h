#pragma once
#include <mutex>

#include "ENEMYTYPE.h"

#define lpHP HP::getInstance()

class HP
{
public:
	static void Destroy(void);
	static HP &getInstance(void)
	{
		Create();
		return *hpIns;
	}

	void EnemyHPDraw(const ENEMYTYPE& type, std::string typeName);
	void PlayerHPDraw(void);

	void UpdatePlayerHP(const int& playerHP,const int& maxHP);
	void SetEnemyHP(const int& enemyHP,const int& maxHP);
private:
	HP();
	~HP();

	static std::once_flag onceflag;
	static HP* hpIns;

	static void Create(void);

	Vector2 barpos[2];

	int enemyHP;
	int enemyMaxHP;
	int playerMaxHP;
	int playerHP;
};

