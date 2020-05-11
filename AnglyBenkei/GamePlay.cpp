#include <DxLib.h>

#include "GameController.h"
#include "SceneShift.h"
#include "GamePlay.h"
#include "GameClear.h"
#include "GameOver.h"
#include "ImageManager.h"
#include "controlledPlayer.h"
#include "Item_Weapon.h"


GamePlay::GamePlay()
{
	Init();

	AddList()(playerList, std::make_unique<controlledPlayer>(Vector2(100, 100),ANIM_WAIT,Vector2(50,50)));

	// ±ÆÒ°¼®İ•¶š—ñ‚ğ¾¯Ä‚³‚¹‚é
	for (auto p = playerList->begin(); p != playerList->end(); p++)
	{
		for (int anim = ANIM_WAIT; anim < ANIM_MAX; anim++)
		{
			(*p)->SetAnimationString(actor[Player_1].animationName[anim], (ANIMATION)anim);
		}
	}
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

	// •¨‘Ì‚ğÁ‹--------------------------------
	SharedWeaponList deleteItemList(itemList->size());
	(*itemList).remove_if([](SharedWeaponPtr& item) {return (item->Getdeleteflag()); });

	for (auto p = playerList->begin(); p != playerList->end(); p++)
	{
		(*p)->UpDate(*gameCtl[Player_1],itemList);
	}
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
	//fileName[weapon][anim].resize(actor[player].frameMax[anim][weapon]);
	//for (int frame = 0; frame < actor[player].frameMax[anim][weapon]; frame++)
	//{
	//	fileName[weapon][anim][frame] = "Image/GamePlay/" + actor[player].playerName[player] + "/" + actor[player].animationName[anim] +
	//		"/" + actor[player].weaponString[weapon] + "/" + actor[player].animationName[anim] + "_" +
	//		std::to_string(frame) + ".png";
	//}
}

bool GamePlay::Init(void)
{
	// ¼°İó‘Ô‚ğGame‚Éİ’è
	lpScene.GetSceneState() = StateGame;

	if (!playerList)
	{
		playerList = make_shared<SharedList>();
	}

	if (!itemList)
	{
		itemList = make_shared<SharedWeaponList>();
	}
	// ÌßÚ²Ô°‚È‚Ì‚©´ÈĞ°‚È‚Ì‚©‚ğ‹æ•Ê‚·‚é‚½‚ß‚Ì•¶š—ñ
	actor[Player_1].playerName = { "Player","Enemy","Boss" };

	// ÌßÚ²Ô°‚Ì±ÆÒ°¼®İÈ°Ñ‚Æ±ÆÒ°¼®İ‚É‰ˆ‚Á‚½Å‘åÌÚ°Ñ”‚Ì‰Šú‰»--------------
	actor[Player_1].animationName =
	{
		"wait",
		"dash",
		"guard",
		"pickup",
		"attack",
	};

	// ’iŠK•¶š—ñ‚Ì‰Šú‰»
	actor[Player_1].levelName =
	{
		"",
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
				LEVEL_NONE,
				LEVEL_NONE,
				LEVEL_NONE,
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



	// -------------------------------------------------------------------

	// ÌßÚ²Ô°‚Ì‰æ‘œ‚ğ˜A”Ô‰æ‘œ‚É‚·‚é‚½‚ß‚É‰æ‘œÌ«ÙÀŞÊß½‚ğì¬

	for (int w = WEAPON_SWORD; w < WEAPON_MAX; w++)
	{
		for (int animation = ANIM_WAIT; animation < ANIM_MAX; animation++)
		{
			InitFrame((ANIMATION)animation, (WEAPON)w, Player_1);
			CreateImageFolderPass((ANIMATION)animation,(WEAPON)w, Player_1);
			lpImageMng.SetAnimationName((ANIMATION)animation,(WEAPON)w, fileName[w][animation]);
			lpImageMng.SetAnimationString(actor[Player_1], (ANIMATION)animation);
		}
	}

	return true;
}

bool GamePlay::InitFrame(const ANIMATION & anim, const WEAPON & weapon,const PLAYER& player)
{
	if (actor[player].frameMax[anim].size() <= 0)
	{
		actor[player].frameMax[anim].resize(1);
		actor[player].frameMax[anim][weapon].resize(actor[player].levelNum[anim][weapon]);
		return true;
	}
	else
	{
		return false;
	}

}

void GamePlay::Draw(void)
{
	ClsDrawScreen();
	DebugDraw();
	// ÌßÚ²Ô°‚Ì•`‰æ
	for (auto p = playerList->begin(); p != playerList->end(); p++)
	{
		(*p)->Draw();
	}
	// oŒ»±²ÃÑ‚Ì•`‰æ
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
