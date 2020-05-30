#include <DxLib.h>

#include "GamePlay.h"
#include "GameController.h"
#include "SpriteManager.h"
#include "controlledPlayer.h"
#include "Enemy.h"
#include "CollisionLoader.h"
#include "Camera.h"
#include "SoundManager.h"

GamePlay::GamePlay()
{
	// initialize this scene
	Init();
	for (auto player = playerList->begin(); player != playerList->end(); player++)
	{
		(*player)->Init(playerSpriteName, actor[Player_1]);
	}

	AddEnemyList()(enemyList, make_unique<Enemy>(Vector2(ScrSize.x - 100, 0), Eanim_Idle, Golem, Direction_Left));
	AddEnemyList()(enemyList, make_unique<Enemy>(Vector2(-50, 0), Eanim_Idle, Mandrake, Direction_Left));

	// loading player collider
	for (int anim = Idle; anim < Animation_Max; anim++)
	{
		for (int level = 0; level < actor[Player_1].animationLevel[(ANIMATION)anim]; level++)
		{
			lpCollisionLoader.LoadPlayerCollider(
				lpCollider.GetPlayerColliderData(),
				(ANIMATION)anim, actor[Player_1].animationLevel[(ANIMATION)anim]);
		}
	}
	for (auto player = playerList->begin(); player != playerList->end(); player++)
	{
		(*player)->SetCollider(lpCollider.GetPlayerColliderData());
	}
	// loading enemy collider
	
	for (int eType = Mandrake; eType < ETYPE_MAX; eType++)
	{
		for (int eAnim = Eanim_Attack; eAnim < Eanim_Max; eAnim++)
		{
			lpCollisionLoader.LoadEnemyCollider(
				lpCollider.GetEnemyColliderData(),
				(EnemyAnimation)eAnim,
				(ENEMYTYPE)eType);
		}
	}

	for (auto enemy = enemyList->begin(); enemy != enemyList->end(); enemy++)
	{
		(*enemy)->SetCollider(lpCollider.GetEnemyColliderData());
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

	ChangeVolumeSoundMem(255 * 50 / 100, lpSoundMng.GetSoundID("BGM")[0]);
	PlaySoundMem(lpSoundMng.GetSoundID("BGM")[0], DX_PLAYTYPE_BACK, false);

	// player action
	for (auto player = playerList->begin(); player != playerList->end(); player++)
	{
		(*player)->UpDate(*gameCtl[Player_1],enemyList);

		// update camera position
		camera->UpDate((*player)->GetPos());
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
	camera = new Camera({0,0});
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
		"knockback",
		"getup",
		"walk",
		"hit"
	};

	enemy.enemyAnimationString = {
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

	enemy.enemyTypeName[Mandrake] = "Mandrake";
	enemy.enemyTypeName[Golem] = "Golem";
	enemy.enemyTypeName[Werewolf] = "Werewolf";

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
	lpSpriteMng.SetEnemyAnimationString(enemy.enemyAnimationString);
	lpSpriteMng.SetEnemySpriteName(enemySpriteName);

	return true;
}

void GamePlay::Draw(void)
{
	// clear screen
	ClearDrawScreen();
	DebugDraw();
	// debug
	DrawFormatString(0, 0, 0xffffff, "Gameplay");
	/*DrawGraph(camera->GetPos().x, camera->GetPos().y,
		lpSpriteMng.GetID("Image/GamePlay/BackGround/BackGroundTest.png")[0], true);*/

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
	// set player collider
	lpCollider.SetPlayerDataFile(actor[Player_1], (ANIMATION)anim);
}

void GamePlay::CreateEnemySpriteFolderPath(EnemyAnimation eAnim, ENEMYTYPE eType)
{

	InitEnemyFrame(eAnim);
	enemySpriteName[eType][eAnim].resize(enemy.enemyFrameMax[eType][eAnim]);

	for (int eFrameNum = 0; eFrameNum < enemy.enemyFrameMax[eType][eAnim]; eFrameNum++)
	{
		enemySpriteName[eType][eAnim][eFrameNum]
			= "Image/GamePlay/" + actor[Player_AI_StandardEnemy].name + "/" + enemy.enemyTypeName[eType] + "/"
			+ enemy.enemyAnimationString[eAnim] + "/" + enemy.enemyAnimationString[eAnim]
			+ "_" + std::to_string(eFrameNum)
			+ ".png";
	}
	lpCollider.SetEnemyDataFile(enemy, eAnim, eType);
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
		case KnockBack:
			actor[player].frameMax[anim] = { 6 };

			break;
		case GetUp:
			actor[player].frameMax[anim] = { 7 };
			break;
		case Walk:
			actor[player].frameMax[anim] = { 6 };
			break;
		case Hit:
			actor[player].frameMax[anim] = { 3 };
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
		enemy.enemyFrameMax[Mandrake][eAnim] = 7;
		enemy.enemyFrameMax[Golem][eAnim] = 18;
		enemy.enemyFrameMax[Werewolf][eAnim] = 7;

		break;
	case Eanim_Dead:
		enemy.enemyFrameMax[Mandrake][eAnim] = 10;
		enemy.enemyFrameMax[Golem][eAnim] = 9;
		enemy.enemyFrameMax[Werewolf][eAnim] = 9;

		break;
	case Eanim_Fall:
		enemy.enemyFrameMax[Mandrake][eAnim] = 2;
		enemy.enemyFrameMax[Golem][eAnim] = 2;
		enemy.enemyFrameMax[Werewolf][eAnim] = 2;

		break;
	case Eanim_Hit:
		enemy.enemyFrameMax[Mandrake][eAnim] = 3;
		enemy.enemyFrameMax[Golem][eAnim] = 3;
		enemy.enemyFrameMax[Werewolf][eAnim] = 3;


		break;
	case Eanim_Idle:
		enemy.enemyFrameMax[Mandrake][eAnim] = 4;
		enemy.enemyFrameMax[Golem][eAnim] = 5;
		enemy.enemyFrameMax[Werewolf][eAnim] = 4;

		break;
	case Eanim_Run:
		enemy.enemyFrameMax[Mandrake][eAnim] = 6;
		enemy.enemyFrameMax[Golem][eAnim] = 6;
		enemy.enemyFrameMax[Werewolf][eAnim] = 6;

		break;
	case Eanim_Jump:
		enemy.enemyFrameMax[Mandrake][eAnim] = 4;
		enemy.enemyFrameMax[Golem][eAnim] = 4;
		enemy.enemyFrameMax[Werewolf][eAnim] = 4;

		break;
	case Eanim_Max:
		break;
	default:
		break;
	}
}
