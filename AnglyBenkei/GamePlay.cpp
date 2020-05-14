#include <DxLib.h>

#include "GameController.h"
#include "SceneShift.h"
#include "GamePlay.h"
#include "GameClear.h"
#include "GameOver.h"
#include "ImageManager.h"
#include "controlledPlayer.h"
#include "Item_Weapon.h"
#include "Enemy.h"


GamePlay::GamePlay()
{
	Init();

	// ｱﾆﾒｰｼｮﾝ文字列をｾｯﾄさせる
	/*for (auto p = playerList->begin(); p != playerList->end(); p++)
	{
		for (int anim = ANIM_WAIT; anim < ANIM_MAX; anim++)
		{
			(*p)->SetAnimationString(actor[Player_1].animationName[anim], (ANIMATION)anim);
		}
	}*/

	for (int w = WEAPON_SWORD; w < WEAPON_MAX; w++)
	{
		AddWeaponList()(itemList,
						std::make_unique<Item_Weapon>
						(Vector2(300 + (w * 100), 480), Vector2(50, 50), (WEAPON)w));
	}
}


GamePlay::~GamePlay()
{
}

ScenePtr GamePlay::SceneUpDate(ScenePtr own, const PlayerController & gameCtl)
{
	auto padNow = gameCtl[Player_1]->GetPadInfo().padInputNow;
	auto padOld = gameCtl[Player_1]->GetPadInfo().padInputOld;

	// 物体を消去--------------------------------
	SharedWeaponList deleteItemList(itemList->size());
	(*itemList).remove_if([](SharedWeaponPtr& item) {return (item->Getdeleteflag()); });

	// プレイヤー
	for (auto p = playerList->begin(); p != playerList->end(); p++)
	{
		(*p)->UpDate(*gameCtl[Player_1],itemList);
	}
	// 雑魚敵
	for (auto e = enemyList->begin(); e != enemyList->end(); e++)
	{
		(*e)->UpDate(playerList);
	}
	// 武器ｱｲﾃﾑ
	for (auto i = itemList->begin(); i != itemList->end(); i++)
	{
		(*i)->UpDate(playerList);
	}

	Draw();
	return move(own);
}

void GamePlay::CreateImageFolderPass(const ANIMATION& anim,
									 const WEAPON& weapon,
									 const PLAYER& player)
{
	if (player == Player_1)
	{
		// まずﾚﾍﾞﾙﾌｫﾙﾀﾞ分を確保
		fileName[anim][weapon].resize(actor[player].levelNum[anim][weapon]);
		// ﾚﾍﾞﾙﾌｫﾙﾀﾞに入っている枚数分確保
		for (auto file = fileName[anim][weapon].begin();
			file != fileName[anim][weapon].end();)
		{
			for (auto f : actor[player].frame[anim][weapon])
			{
				file->resize(f);
				file++;
			}
		}
		// 画像ﾊﾟｽである文字列を各変数に格納
		for (int level = 0; level < actor[player].frame[anim][weapon].size(); level++)
		{
			for (int frame = 0; frame < actor[player].frame[anim][weapon][level]; frame++)
			{
				if (anim != ANIM_ATTACK)
				{
					fileName[anim][weapon][level][frame] = "Image/GamePlay/" + actor[player].playerName + "/" + actor[player].animationName[anim] +
						"/" + actor[player].weaponString[weapon] + "/" + actor[player].animationName[anim] + "_" +
						std::to_string(frame) + ".png";
				}
				else
				{
					fileName[anim][weapon][level][frame] = "Image/GamePlay/" + actor[player].playerName + "/" + actor[player].animationName[anim] +
						"/" + actor[player].weaponString[weapon] + "/" + actor[player].levelName[level] + "/" + actor[player].animationName[anim]
						+ std::to_string(level + 1) + "_" +
						std::to_string(frame) + ".png";
				}
			}
		}
	}
	if (player == Player_AI_StandardEnemy)
	{
		if (enemyFrameMax[player - 1][anim] > 0 && enemyFileName[player - 1][anim].size() <= 0)
		{
			enemyFileName[player - 1][anim].resize(enemyFrameMax[player - 1][anim]);

			for (int num = 0; num < enemyFrameMax[player - 1][anim]; num++)
			{
				enemyFileName[player - 1][anim][num] = "Image/GamePlay/" + actor[player].playerName + "/" + actor[player].animationName[anim] +
					"/" + actor[player].animationName[anim] + "_" +
					std::to_string(num) + ".png";
			}
		}
	}
}

bool GamePlay::Init(void)
{
	// ｼｰﾝ状態をGameに設定
	lpScene.GetSceneState() = StateGame;

	if (!playerList)
	{
		playerList = make_shared<SharedList>();
	}
	if (!enemyList)
	{
		enemyList = make_shared<SharedEnemyList>();
	}

	if (!itemList)
	{
		itemList = make_shared<SharedWeaponList>();
	}

	AddList()(playerList, std::make_unique<controlledPlayer>(Vector2(100, 100), ANIM_WAIT, Vector2(50, 50)));
	AddEnemyList()(enemyList, std::make_unique<Enemy>(Vector2(100, 100), ANIM_WAIT,StandardEnemy));

	// ﾌﾟﾚｲﾔｰなのかｴﾈﾐｰなのかを区別するための文字列
	actor[Player_1].playerName = "Player";
	actor[Player_AI_StandardEnemy].playerName = "Enemy";


	// ﾌﾟﾚｲﾔｰのｱﾆﾒｰｼｮﾝﾈｰﾑとｱﾆﾒｰｼｮﾝに沿った最大ﾌﾚｰﾑ数の初期化--------------
	actor[Player_1].animationName =
	{
		"wait",
		"dash",
		"guard",
		"pickup",
		"attack",
	};
	actor[Player_AI_StandardEnemy].animationName =
	{
		"wait",
		"dash",
		"guard",
		"",
		"attack",
	};

	// 段階文字列の初期化
	actor[Player_1].levelName =
	{
		"level1",
		"level2",
		"level3",
		"level4",
		"level5"
	};


	for (int animation = ANIM_WAIT; animation < ANIM_MAX; animation++)
	{
		if (animation != ANIM_ATTACK)
		{
			actor[Player_1].levelNum[(ANIMATION)animation] =
			{
				LEVEL_NONE + 1,
				LEVEL_NONE + 1,
				LEVEL_NONE + 1,
				LEVEL_NONE + 1,
				LEVEL_NONE + 1,
				LEVEL_NONE + 1,
				LEVEL_NONE + 1,
				LEVEL_NONE + 1
			};
		}
		else
		{
			actor[Player_1].levelNum[(ANIMATION)animation] =
			{
				LEVEL_3,
				LEVEL_3,
				LEVEL_3,
				LEVEL_3,
				LEVEL_NONE,
				LEVEL_NONE,
				LEVEL_NONE,
				LEVEL_NONE
			};
		}
	}
	actor[Player_1].weaponString =
	{
		"Sword",
		"Spear",
		"Axe",
		"Hammer",
		"Tongfer",
		"Jitte",
		"Naginata",
		"None"
	};

	enemyFrameMax[StandardEnemy] =
	{
		5,5,0,0,4
	};

	// -------------------------------------------------------------------

	// ﾌﾟﾚｲﾔｰの画像を連番画像にするために画像ﾌｫﾙﾀﾞﾊﾟｽを作成
	for (int animation = ANIM_WAIT; animation < ANIM_MAX; animation++)
	{
		for (int w = WEAPON_SWORD; w < WEAPON_MAX; w++)
		{
			InitFrame((ANIMATION)animation, (WEAPON)w, Player_1);
			CreateImageFolderPass((ANIMATION)animation, (WEAPON)w, Player_1);
			CreateImageFolderPass((ANIMATION)animation, (WEAPON)w, Player_AI_StandardEnemy);

			for (auto p = playerList->begin(); p != playerList->end(); p++)
			{
				lpImageMng.SetAnimationName((ANIMATION)animation,
											(WEAPON)w,
											fileName[animation][w],
											(*p)->GetAnimLevel((ANIMATION)animation,(WEAPON)w));
			}
			// 雑魚敵のｱﾆﾒｰｼｮﾝ画像ｾｯﾄ
			lpImageMng.SetAnimationName((ANIMATION)animation,StandardEnemy, enemyFileName[StandardEnemy][(ANIMATION)animation]);
			lpImageMng.SetAnimationString(actor[Player_1].animationName[animation],Player_1, (ANIMATION)animation);
		}
	}

	for (int anim = ANIM_WAIT; anim < ANIM_MAX; anim++)
	{
		lpImageMng.SetAnimationString(actor[Player_AI_StandardEnemy].animationName[anim], Player_AI_StandardEnemy, (ANIMATION)anim);
	}

	return true;
}

bool GamePlay::InitFrame(const ANIMATION & anim, const WEAPON & weapon,const PLAYER& player)
{
	//if (actor[player].frameMax[anim].size() <= 0)
	{
		//actor[player].frame[anim][weapon].resize(1);
	}
	if (player == Player_1)
	{
		if (actor[player].frame[anim][weapon].size() <= 0)
		{
			actor[player].frame[anim][weapon].resize(actor[player].levelNum[anim][weapon]);
		}
		//// 画像枚数分を格納
		switch (anim)
		{
		case ANIM_WAIT:
			actor[player].frame[anim][weapon][0] = 5;
			break;

		case ANIM_DASH:
			actor[player].frame[anim][weapon][0] = 2;

			break;
		case ANIM_GUARD:
			actor[player].frame[anim][weapon][0] = 2;

			break;
		case ANIM_PICKUP:
			actor[player].frame[anim][weapon][0] = 5;

			break;
		case ANIM_ATTACK:
			switch (weapon)
			{
			case WEAPON_SWORD:
				actor[player].frame[anim][weapon] = { 3,3,3 };

				break;
			case WEAPON_SPEAR:

				break;
			case WEAPON_AXE:

				break;
			case WEAPON_HAMMER:
				break;
			case WEAPON_TONGFAR:
				break;
			case WEAPON_JITTE:
				break;

			}
			break;
		}
	}
	return true;
}

void GamePlay::Draw(void)
{
	ClsDrawScreen();
	DebugDraw();

	// プレイヤーの描画
	for (auto p = playerList->begin(); p != playerList->end(); p++)
	{
		(*p)->Draw();
	}
	// 敵の描画
	for (auto e = enemyList->begin(); e != enemyList->end(); e++)
	{
		(*e)->Draw();
	}
	// 出現ｱｲﾃﾑの描画
	for (auto i = itemList->begin(); i != itemList->end(); i++)
	{
		(*i)->Draw();
	}

	ScreenFlip();
}

void GamePlay::DebugDraw(void)
{
	DrawFormatString(0, 0, 0xffffff, "GamePlay");
}
