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

	// ��Ұ��ݕ������Ă�����
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

	// ���̂�����--------------------------------
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
	// �܂�����̫��ޕ����m��
	fileName[anim][weapon].resize(actor[player].levelNum[anim][weapon]);
	// ����̫��ނɓ����Ă��閇�����m��
	for (auto file = fileName[anim][weapon].begin();
		 file != fileName[anim][weapon].end();)
	{
		for (auto f : actor[player].frame[anim][weapon])
		{
			file->resize(f);
			file++;
		}
	}
	// �摜�߽�ł��镶������e�ϐ��Ɋi�[
	for (int level = 0; level < actor[player].frame[anim][weapon].size(); level++)
	{
		for (int frame = 0; frame < actor[player].frame[anim][weapon][level]; frame++)
		{
			if (anim != ANIM_ATTACK)
			{
				fileName[anim][weapon][level][frame] = "Image/GamePlay/" + actor[player].playerName[player] + "/" + actor[player].animationName[anim] +
					"/" + actor[player].weaponString[weapon] + "/" + actor[player].animationName[anim] + "_" +
					std::to_string(frame) + ".png";
			}
			else
			{
				fileName[anim][weapon][level][frame] = "Image/GamePlay/" + actor[player].playerName[player] + "/" + actor[player].animationName[anim] +
					"/" + actor[player].weaponString[weapon] + "/" + actor[player].levelName[level] + "/" + actor[player].animationName[anim]
					+ std::to_string(level + 1) + "_" +
					std::to_string(frame) + ".png";
			}
		}
	}
}

bool GamePlay::Init(void)
{
	// ��ݏ�Ԃ�Game�ɐݒ�
	lpScene.GetSceneState() = StateGame;

	if (!playerList)
	{
		playerList = make_shared<SharedList>();
	}

	if (!itemList)
	{
		itemList = make_shared<SharedWeaponList>();
	}

	AddList()(playerList, std::make_unique<controlledPlayer>(Vector2(100, 100), ANIM_WAIT, Vector2(50, 50)));

	// ��ڲ԰�Ȃ̂���а�Ȃ̂�����ʂ��邽�߂̕�����
	actor[Player_1].playerName = { "Player","Enemy","Boss" };

	// ��ڲ԰�̱�Ұ���ȰтƱ�Ұ��݂ɉ������ő��ڰѐ��̏�����--------------
	actor[Player_1].animationName =
	{
		"wait",
		"dash",
		"guard",
		"pickup",
		"attack",
	};

	// �i�K������̏�����
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



	// -------------------------------------------------------------------

	// ��ڲ԰�̉摜��A�ԉ摜�ɂ��邽�߂ɉ摜̫����߽���쐬
	for (int animation = ANIM_WAIT; animation < ANIM_MAX; animation++)
	{
		for (int w = WEAPON_SWORD; w < WEAPON_MAX; w++)
		{
			InitFrame((ANIMATION)animation, (WEAPON)w, Player_1);
			CreateImageFolderPass((ANIMATION)animation, (WEAPON)w, Player_1);
			for (auto p = playerList->begin(); p != playerList->end(); p++)
			{
				lpImageMng.SetAnimationName((ANIMATION)animation,
											(WEAPON)w,
											fileName[animation][w],
											(*p)->GetAnimLevel((ANIMATION)animation,(WEAPON)w));
			}
			lpImageMng.SetAnimationString(actor[Player_1], (ANIMATION)animation);
		}
	}
	return true;
}

bool GamePlay::InitFrame(const ANIMATION & anim, const WEAPON & weapon,const PLAYER& player)
{
	//if (actor[player].frameMax[anim].size() <= 0)
	{
		//actor[player].frame[anim][weapon].resize(1);
	}
	if (actor[player].frame[anim][weapon].size() <= 0)
	{
		actor[player].frame[anim][weapon].resize(actor[player].levelNum[anim][weapon]);
	}
	//// �摜���������i�[
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



	return true;
}

void GamePlay::Draw(void)
{
	ClsDrawScreen();
	DebugDraw();
	// ��ڲ԰�̕`��
	for (auto p = playerList->begin(); p != playerList->end(); p++)
	{
		(*p)->Draw();
	}
	// �o�����т̕`��
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
