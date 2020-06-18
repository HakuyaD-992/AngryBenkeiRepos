#include <DxLib.h>

#include "SceneShift.h"
#include "SpriteManager.h"

#include "HP.h"

std::once_flag HP::onceflag;
HP* HP::hpIns = nullptr;

void HP::Destroy(void)
{
	if (hpIns != nullptr)
	{
		delete hpIns;
	}
	hpIns = nullptr;
}

void HP::EnemyHPDraw(const ENEMYTYPE& type,std::string typeName)
{
	if (enemyHP > 0)
	{
		DrawRotaGraph(barpos[1].x, barpos[1].y, 1.0f, 0.0f, lpSpriteMng.GetEnemySpriteID(type, typeName, "hpbar")[0], true, false);

		DrawBox(barpos[1].x - (enemyMaxHP / 2), barpos[1].y - (22 / 2),
			(barpos[1].x + enemyHP), barpos[1].y + (20 / 2),
			0xaaaa00, true);

		DrawRotaGraph(600, 130, 1.0f, 0.0f, lpSpriteMng.GetEnemySpriteID(type, typeName, "name")[0], true, false);

	}
}

void HP::PlayerHPDraw(void)
{
	DrawRotaGraph(barpos[0].x - 100, barpos[0].y - 35, 1.0f, 0.0f, lpSpriteMng.GetPlayerSpriteID("HPname")[0], true, false);
	DrawRotaGraph(barpos[0].x, barpos[0].y, 1.0f, 0.0f, lpSpriteMng.GetPlayerSpriteID("hpbar")[0], true, false);

	DrawBox(barpos[0].x - playerMaxHP, barpos[0].y - (22 / 2),
		(barpos[0].x + playerHP), barpos[0].y + (20 / 2),
		0xaaaa00, true);


}

void HP::UpdatePlayerHP(const int & playerHP,const int& maxHP)
{
	this->playerHP = playerHP;
	this->playerMaxHP = maxHP;
}

void HP::SetEnemyHP(const int & enemyHP, const int& maxHP)
{
	this->enemyHP = enemyHP;
	this->enemyMaxHP = maxHP;
}

HP::HP()
{
	// player hp bar
	barpos[0] = { lpScene.GetScreenSize().x / 2 - 200,90 };
	// enemy hp bar
	barpos[1] = { lpScene.GetScreenSize().x / 2 + 200,90 };

}


HP::~HP()
{
}

void HP::Create(void)
{
	if (hpIns == nullptr)
	{
		hpIns = new HP();
	}
}
