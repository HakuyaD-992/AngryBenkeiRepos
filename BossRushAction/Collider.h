#pragma once
#include <vector>
#include <array>
#include <mutex>

#include "Vector2.h"
#include "EnemyAnimation.h"
#include "ANIMATION.h"
#include "AnimationLevel.h"
#include "ENEMYTYPE.h"
#include "GamePlay.h"

#define lpCollider Collider::getInstance()

enum RectState
{
	R_State_Damage,
	R_State_Attack,
	R_State_Max
};

// rectangle's position
typedef std::vector<Vector2> RPos;

// frame
struct ActionRect
{
	RPos pos[R_State_Max];
	RPos size[R_State_Max];
	int rectNum[R_State_Max];
	std::string fileName;
};

// animation
struct PlayerAnimationRectData
{
	// 1±∆“∞ºÆ›ÇÃëçÃ⁄∞—êî
	int totalFrame_player;
	std::vector<ActionRect> playerRectData;
};

// level
struct PlayerAnimLevelRectData
{
	std::vector<PlayerAnimationRectData> playerAnimLevelData;
};

struct EnemyFrameRectData
{
	int totalFrame_enemy;
	std::vector<ActionRect> enemyFrameRectData;
};

struct EnemyAnimationRectData
{
	std::array<EnemyFrameRectData,Eanim_Max> enemyAnimationRectData;
};
using PlayerRectData = std::array<PlayerAnimLevelRectData, Animation_Max>;
using EnemyRectData = std::array<EnemyAnimationRectData, ETYPE_MAX>;

class Collider
{
public:
	static void Destroy(void);
	static Collider &getInstance(void)
	{
		Create();
		return *colliderIns;
	}

	// initialize player collision data 
	void SetPlayerDataFile(const Actor& actor,
						 const ANIMATION& pAnimation);
	void SetEnemyDataFile(const EnemyStructure& enemy,
						  const EnemyAnimation& eAnimation,
						  const ENEMYTYPE& eType);

	// get data file
	PlayerRectData& GetPlayerColliderData(void)
	{
		return playerCollider;
	}

	// get enemy data file
	EnemyRectData& GetEnemyColliderData(void)
	{
		return enemyCollider;
	}

private:
	Collider();
	~Collider();

	static std::once_flag onceflag;
	static Collider* colliderIns;

	static void Create(void);
	PlayerRectData playerCollider;
	EnemyRectData enemyCollider;
};

