#include <DxLib.h>

#include "GamePlay.h"
#include "GameOver.h"
#include "GameController.h"
#include "SpriteManager.h"
#include "controlledPlayer.h"
#include "Enemy.h"
#include "CollisionLoader.h"
#include "Camera.h"
#include "SoundManager.h"
#include "HP.h"

GamePlay::GamePlay()
{
	// initialize this scene
	Init();
	for (auto player = playerList->begin(); player != playerList->end(); player++)
	{
		(*player)->Init(playerSpriteName, actor[Player_1]);
	}

	// loading player collider
	for (int anim = Idle; anim < Animation_Max; anim++)
	{
		lpCollisionLoader.LoadPlayerCollider(
			lpCollider.GetPlayerColliderData(),
			(ANIMATION)anim, actor[Player_1].animationLevel[(ANIMATION)anim]);
	}
	for (auto player = playerList->begin(); player != playerList->end(); player++)
	{
		(*player)->SetCollider(lpCollider.GetPlayerColliderData());
	}
	// loading enemy collider
	
	for (int type = BigBoy;type < Engineer;type++)
	{
		for (int eAnim = Eanim_Attack; eAnim < Eanim_Max; eAnim++)
		{
			lpCollisionLoader.LoadEnemyCollider(
				lpCollider.GetEnemyColliderData(),
				(EnemyAnimation)eAnim,
				(ENEMYTYPE)type);
		}
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

	ChangeVolumeSoundMem(255 * 60 / 100, lpSoundMng.GetSoundID("BGM")[0]);
	if (!CheckSoundMem(lpSoundMng.GetSoundID("BGM")[0]))
	{
		PlaySoundMem(lpSoundMng.GetSoundID("BGM")[0], DX_PLAYTYPE_BACK, false);
	}

	// íœ‚·‚éÌßÚ²Ô°Ø½Ä‚Ìì¬
	SharedPlayerList deleteCharaList(playerList->size());
	(*playerList).remove_if([](SharedPlayerPtr& obj) {return (obj->Getdeleteflag()); });



	if (frame % 100 == 0)
	{
		AddEnemyList()(enemyList, make_unique<Enemy>(Vector2(ScrSize.x - 100, 0), Eanim_Idle, BigBoy, Direction_Left));
	}

	// player action
	for (auto player = playerList->begin(); player != playerList->end(); player++)
	{
		(*player)->UpDate(*gameCtl[Player_1],enemyList);

		// update camera position
		camera->UpDate((*player)->GetPos());


		if ((*player)->Getdeleteflag())
		{
			gameOverFlag = true;
		}
		else
		{
			frame++;
		}
	}

	// íœ‚·‚é“G‚ÌØ½Ä‚Ìì¬
	SharedEnemyList deleteEnemyList(enemyList->size());
	(*enemyList).remove_if([](SharedEnemyPtr& obj) {return (obj->Getdeleteflag()); });

	if (gameOverFlag)
	{
		StopSoundMem(lpSoundMng.GetSoundID("BGM")[0]);
		lpCollisionLoader.Destroy();
		lpCollider.Destroy();
		lpSoundMng.Destroy();
		lpSpriteMng.Destroy();

		return std::make_unique<GameOver>();
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
		Level_5,
		Level_3,
		Level_1,
		Level_1,
		Level_1,
		Level_1,
		Level_1,
		Level_1,
		Level_1,
		Level_1,
		Level_1,
	};
	actor[Player_1].animationString = {
		"idle",
		"attack",
		"attack_sword",
		"jump",
		"attack_jump_sword",
		"fall",
		"run",
		"summersault",
		"knockdown",
		"getup",
		"walk",
		"hit"
	};

	enemy.enemyAnimationString = {
		"attack",
		"dead",
		"hit",
		"idle",
		"walk",
	};
	// initialize individuals folder name
	actor[Player_1].name = "Player";
	actor[Player_AI_StandardEnemy].name = "Enemy";

	enemy.enemyTypeName[BigBoy] = "BigBoy";
	enemy.enemyTypeName[Engineer] = "Engineer";
	enemy.enemyTypeName[Shieldman] = "Shieldman";
	enemy.enemyTypeName[Soldier] = "Soldier";
	enemy.enemyTypeName[Watcher] = "Watcher";

	for (int anim = Idle; anim < Animation_Max; anim++)
	{
		CreateSpriteFolderPath((ANIMATION)anim, Player_1);
	}

	for (int eType = BigBoy; eType < ETYPE_MAX; eType++)
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

	frame = 0;
	gameOverFlag = false;

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
		lpHP.PlayerHPDraw();
		if ((*player)->GetisHitEnemyType() < ETYPE_MAX)
		{
			lpHP.EnemyHPDraw((*player)->GetisHitEnemyType(), enemy.enemyTypeName[(*player)->GetisHitEnemyType()]);
		}
	}

	// draw enemies
	for (auto e = enemyList->begin(); e != enemyList->end(); e++)
	{
		(*e)->Draw();

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
		case Attack:
			actor[player].frameMax[anim] = { 3,3,3,4,4 };

			break;
		case Attack_Sword:
			actor[player].frameMax[anim] = { 6,6,5 };
			break;
		case Jump:
			actor[player].frameMax[anim] = { 4 };
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
		case KnockDown:
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
		enemy.enemyFrameMax[BigBoy][eAnim] = 10;
		enemy.enemyFrameMax[Engineer][eAnim] = 12;
		enemy.enemyFrameMax[Shieldman][eAnim] = 10;
		enemy.enemyFrameMax[Soldier][eAnim] = 8;
		enemy.enemyFrameMax[Watcher][eAnim] = 17;

		break;
	case Eanim_Dead:
		enemy.enemyFrameMax[BigBoy][eAnim] = 13;
		enemy.enemyFrameMax[Engineer][eAnim] = 10;
		enemy.enemyFrameMax[Shieldman][eAnim] = 10;
		enemy.enemyFrameMax[Soldier][eAnim] = 15;
		enemy.enemyFrameMax[Watcher][eAnim] = 13;
		break;
	case Eanim_Hit:
		enemy.enemyFrameMax[BigBoy][eAnim] = 6;
		enemy.enemyFrameMax[Engineer][eAnim] = 4;
		enemy.enemyFrameMax[Shieldman][eAnim] = 6;
		enemy.enemyFrameMax[Soldier][eAnim] = 6;
		enemy.enemyFrameMax[Watcher][eAnim] = 8;
		break;
	case Eanim_Idle:
		enemy.enemyFrameMax[BigBoy][eAnim] = 6;
		enemy.enemyFrameMax[Engineer][eAnim] = 6;
		enemy.enemyFrameMax[Shieldman][eAnim] = 6;
		enemy.enemyFrameMax[Soldier][eAnim] = 6;
		enemy.enemyFrameMax[Watcher][eAnim] = 6;
		break;
	case Eanim_Walk:
		enemy.enemyFrameMax[BigBoy][eAnim] = 7;
		enemy.enemyFrameMax[Engineer][eAnim] = 10;
		enemy.enemyFrameMax[Shieldman][eAnim] = 10;
		enemy.enemyFrameMax[Soldier][eAnim] = 9;
		enemy.enemyFrameMax[Watcher][eAnim] = 9;
		break;
	case Eanim_Max:
		break;
	default:
		break;
	}
}
