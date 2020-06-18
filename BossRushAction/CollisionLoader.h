#pragma once
#include <mutex>
#include "ANIMATION.h"
#include "EnemyAnimation.h"
#include "ENEMYTYPE.h"
#include "AnimationLevel.h"
#include "EnemyAnimation.h"
#include "Collider.h"

// collision load
#define lpCollisionLoader CollisionLoader::getInstance()

// data header
struct PlayerDataHeader
{
	int dataNum[R_State_Max];
};
using PlayerHeader = std::vector<PlayerDataHeader>;

struct EnemyDataHeader
{
	int dataNum[R_State_Max];
};
using EnemyHeader = std::array<std::vector<EnemyDataHeader>,ETYPE_MAX>;

class CollisionLoader
{
public:
	static void Destroy(void);
	static CollisionLoader &getInstance(void)
	{
		Create();
		return *colLoaderIns;
	}

	void LoadPlayerCollider(PlayerRectData& playerData,
							const ANIMATION& pAnimation,
							const AnimationLevel& animlevel);
	void LoadEnemyCollider(EnemyRectData& enemyData,
						   const EnemyAnimation& eAnimation,
						   const ENEMYTYPE& eType);
private:
	CollisionLoader();
	~CollisionLoader();

	static std::once_flag onceflag;
	static CollisionLoader* colLoaderIns;

	static void Create(void);

	FILE* playerDataHeaderFile;
	FILE* enemyDataHeaderFile;

	FILE* playerDataFile;
	FILE* enemyDataFile;

	std::vector<PlayerHeader> playerDataHeader[Animation_Max];
	EnemyHeader enemyDataHeader[Eanim_Max];
};

