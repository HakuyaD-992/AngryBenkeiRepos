#include <DxLib.h>

#include "GamePlay.h"
#include "GameController.h"
#include "SpriteManager.h"
#include "controlledPlayer.h"
#include "Enemy.h"


GamePlay::GamePlay()
{
	// initialize this scene
	Init();

	for (auto player = playerList->begin(); player != playerList->end(); player++)
	{
		(*player)->Init(playerSpriteName, actor[Player_1].animationLevel);
	}
	for (auto enemy = enemyList->begin(); enemy != enemyList->end(); enemy++)
	{
		(*enemy)->Init(enemySpriteName);
	}
}


GamePlay::~GamePlay()
{
}

ScenePtr GamePlay::SceneUpDate(ScenePtr own, const PlayerController & gameCtl)
{
	// input information(Gamepad)
	auto inputNow = gameCtl[Player_1]->GetPadInfo().padInputNow;
	auto inputOld = gameCtl[Player_1]->GetPadInfo().padInputOld;

	// player action
	for (auto player = playerList->begin(); player != playerList->end(); player++)
	{
		(*player)->UpDate(*gameCtl[Player_1]);
	}
	// enemies action
	for (auto enemy = enemyList->begin(); enemy != enemyList->end(); enemy++)
	{
		(*enemy)->UpDate(playerList);
	}

	// draw something
	Draw();

	return move(own);
}

bool GamePlay::Init(void)
{
	// create player list
	if (!playerList)
	{
		playerList = make_shared<SharedPlayerList>();
	}
	if (!enemyList)
	{
		enemyList = make_shared<SharedEnemyList>();
	}

	AddPlayerList()(playerList, make_unique<controlledPlayer>(Vector2(100, 100), Idle, Direction_Right));

	AddEnemyList()(enemyList, make_unique<Enemy>(Vector2(500,0), Eanim_Idle, Golem, Direction_Left));

	// initialize player animation level
	actor[Player_1].animationLevel = {
		Level_1,
		Level_2,
		Level_3,
		Level_1,
		Level_3,
		Level_1,
		Level_1,
		Level_1,
		Level_1,
		Level_1
	};
	actor[Player_1].animationString = {
		"idle",
		"kick",
		"attack_sword",
		"jump",
		"punch",
		"attack_jump_sword",
		"fall",
		"run",
		"summersault",
		"dead"
	};

	// initialize enemy's animation level
	enemyAnimationLevelMax = { 
		Level_2,
		Level_1,
		Level_1,
		Level_1,
		Level_1,
		Level_1,
		Level_1,
	};
	enemyAnimationString = {
		"attack",
		"dead",
		"fall",
		"hit",
		"idle",
		"run",
		"jump"
	};
	// initialize individuals folder name
	actor[Player_1].name = "Player";
	actor[Player_AI_StandardEnemy].name = "Enemy";

	enemyTypeName[Mandrake] = "Mandrake";
	enemyTypeName[Golem] = "Golem";
	enemyTypeName[Werewolf] = "Werewolf";

	for (int anim = Idle; anim < Animation_Max; anim++)
	{
		CreateSpriteFolderPath((ANIMATION)anim, Player_1);
	}

	for (int eType = Mandrake; eType < ETYPE_MAX; eType++)
	{
		for (int eAnim = Eanim_Attack; eAnim < Eanim_Max; eAnim++)
		{
			CreateEnemySpriteFolderPath((EnemyAnimation)eAnim, (ENEMYTYPE)eType);
		}
	}
	// set animation strings(player)
	lpSpriteMng.SetPlayerAnimationString(actor[Player_1].animationString);
	lpSpriteMng.SetPlayerSpriteName(playerSpriteName);
	// set animation strings(enemy)
	lpSpriteMng.SetEnemyAnimationString(enemyAnimationString);

	return true;
}

void GamePlay::Draw(void)
{
	// clear screen
	ClearDrawScreen();
	DebugDraw();
	// debug
	DrawFormatString(0, 0, 0xffffff, "Gameplay");

	// draw player
	for (auto player = playerList->begin(); player != playerList->end(); player++)
	{
		(*player)->Draw();
	}

	// draw enemies
	for (auto enemy = enemyList->begin(); enemy != enemyList->end(); enemy++)
	{
		(*enemy)->Draw();
	}

	// flip screen
	ScreenFlip();
}

void GamePlay::DebugDraw(void)
{
}

void GamePlay::CreateSpriteFolderPath(ANIMATION anim,PLAYER player)
{
	// initialize frame
	InitPlayerFrame(anim, player);

	playerSpriteName[anim].resize(actor[player].animationLevel[anim]);

	for (int level = 0; level < actor[player].animationLevel[anim]; level++)
	{
		playerSpriteName[anim][level].resize(actor[player].frameMax[anim][level]);
		for (int frame = 0; frame < actor[player].frameMax[anim][level]; frame++)
		{
			playerSpriteName[anim][level][frame]
				= "Image/GamePlay/" + actor[player].name + "/" + actor[player].animationString[anim]
				+ "/" + std::to_string(level + 1) + "/"+ actor[player].animationString[anim]
				+ std::to_string(level + 1) + "_" + std::to_string(frame) + ".png";
		}
	}
}

void GamePlay::CreateEnemySpriteFolderPath(EnemyAnimation eAnim, ENEMYTYPE eType)
{

	InitEnemyFrame(eAnim);
	enemySpriteName[eType][eAnim].resize(enemyFrameMax[eType][eAnim]);

	for (int eFrameNum = 0; eFrameNum < enemyFrameMax[eType][eAnim]; eFrameNum++)
	{
		enemySpriteName[eType][eAnim][eFrameNum]
			= "Image/GamePlay/" + actor[Player_AI_StandardEnemy].name + "/" + enemyTypeName[eType] + "/"
			+ enemyAnimationString[eAnim] + "/" + enemyAnimationString[eAnim]
			+ "_" + std::to_string(eFrameNum)
			+ ".png";
	}
}

void GamePlay::InitPlayerFrame(ANIMATION anim, PLAYER player)
{
	if (player == Player_1)
	{
		// resize maxframe
		actor[player].frameMax[anim].resize(actor[player].animationLevel[anim]);
		switch (anim)
		{
		case Idle:

			actor[player].frameMax[anim] = { 5 };
			break;
		case Kick:
			actor[player].frameMax[anim] = { 4,4 };

			break;
		case Attack_Sword:
			actor[player].frameMax[anim] = { 5,6,6 };

			break;
		case Jump:
			actor[player].frameMax[anim] = { 4 };

			break;
		case Punch:
			actor[player].frameMax[anim] = { 5,4,6 };

			break;
		case Attack_Jump_Sword:
			actor[player].frameMax[anim] = { 4 };

			break;
		case Fall:
			actor[player].frameMax[anim] = { 2 };

			break;
		case Run:
			actor[player].frameMax[anim] = { 6 };

			break;
		case SummerSault:
			actor[player].frameMax[anim] = { 3 };

			break;
		case Dead:
			actor[player].frameMax[anim] = { 7 };

			break;
		case Animation_Max:
			break;
		default:
			break;
		}
	}

}

void GamePlay::InitEnemyFrame(EnemyAnimation eAnim)
{
	switch (eAnim)
	{
	case Eanim_Attack:
		enemyFrameMax[Mandrake][eAnim] = 7;
		enemyFrameMax[Golem][eAnim] = 18;
		enemyFrameMax[Werewolf][eAnim] = 7;

		break;
	case Eanim_Dead:
		enemyFrameMax[Mandrake][eAnim] = 10;
		enemyFrameMax[Golem][eAnim] = 9;
		enemyFrameMax[Werewolf][eAnim] = 9;

		break;
	case Eanim_Fall:
		enemyFrameMax[Mandrake][eAnim] = 2;
		enemyFrameMax[Golem][eAnim] = 2;
		enemyFrameMax[Werewolf][eAnim] = 2;

		break;
	case Eanim_Hit:
		enemyFrameMax[Mandrake][eAnim] = 3;
		enemyFrameMax[Golem][eAnim] = 3;
		enemyFrameMax[Werewolf][eAnim] = 3;


		break;
	case Eanim_Idle:
		enemyFrameMax[Mandrake][eAnim] = 4;
		enemyFrameMax[Golem][eAnim] = 5;
		enemyFrameMax[Werewolf][eAnim] = 4;

		break;
	case Eanim_Run:
		enemyFrameMax[Mandrake][eAnim] = 6;
		enemyFrameMax[Golem][eAnim] = 6;
		enemyFrameMax[Werewolf][eAnim] = 6;

		break;
	case Eanim_Jump:
		enemyFrameMax[Mandrake][eAnim] = 4;
		enemyFrameMax[Golem][eAnim] = 4;
		enemyFrameMax[Werewolf][eAnim] = 4;

		break;
	case Eanim_Max:
		break;
	default:
		break;
	}
}
