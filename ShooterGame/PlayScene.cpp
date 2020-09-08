#include <DxLib.h>
#include "Application.h"
#include "PlayScene.h"
#include "ScreenEffectMng.h"
#include "ImageManager.h"
#include "Input.h"
#include "PLAYER.h"
#include "ControlledPlayer.h"
#include "Floor.h"
#include "WeaponBase.h"
#include "Spawner.h"
#include "Enemy.h"
#include "BackGround.h"
#include "AICollider.h"
#include "EnemyAIManager.h"
#include "PodAI.h"
#include "EnemyBullet.h"
#include "SoundManager.h"

PlayScene::PlayScene(SceneController& sCon):
	BaseScene(sCon)
{
	Initialize();

	lpSound.Play("bgm", 255 * 70 / 100, DX_PLAYTYPE_LOOP);
}

PlayScene::~PlayScene()
{
}

void PlayScene::UpDate(const std::vector<std::shared_ptr<Input>>& input)
{
	fps_.Update();

	auto inputData1_ = input[static_cast<int>(PLAYER::ONE)]->GetPeriData();
	auto inputData2_ = input[static_cast<int>(PLAYER::TWO)]->GetPeriData();

	if (frame_ % 100 == 0)
	{
		// �G�̕���
		spawner_->MakeClone(enemyList_, playerList_);
		for (auto enemy : enemyList_)
		{
			lpS_Effect.GetEnemy(enemy);
		}
	}
	for (auto enemy : enemyList_)
	{
		aiManager_->UpDate(enemy);

		// �G�̱�Ұ��݊֌W
		enemy->Action();

		auto type = enemy->GetType();

		switch (type)
		{
		case ActorType::Pod:
			if (enemy->GetCurrentAnimation() == "attack_release")
			{
				enemy->AddBullet(enemyBullets_);
			}
			else
			{
				enemy->ReadyToShot();
			}
			break;
		case ActorType::Exoskeleton:
			break;
		case ActorType::Roboid:
		default:
			break;
		}
	}

	for (auto b : enemyBullets_)
	{
		b->UpDate();
	}
	for (auto player : playerList_)
	{
		player->UpDate();
		player->GetCurrentWeapon()->UpDate();
	}
	lpS_Effect.UpDate(EFFECT_TYPE::non);
	enemyList_.remove_if
	([](std::shared_ptr<Enemy>& enemy) {return enemy->GetDeleteFlag(); });

	fps_.Wait();
	frame_++;
}

void PlayScene::Draw(void)
{
	auto& app = Application::Instance();
	auto scr = app.GetViewport().GetSize();

	ClearDrawScreen();

	DrawFormatString(0, 0, 0xffffff, "GamePlay");
	DrawRotaGraph(scr.x / 2, scr.y / 2 - 106,
		1.0f, 0.0f,
		lpImage.GetDivID(currentWeather_)[0], true);

	for (auto obj : objList_)
	{
		obj->Draw();
	}

	for (auto b : enemyBullets_)
	{
		b->Draw();
	}

	for (auto player : playerList_)
	{
		DrawPlayer(player);
	}

	for (auto enemy : enemyList_)
	{
		enemy->Draw_();
		enemy->GetAICollider()->Draw();
	}
	fps_.Draw();
	
	//DrawRotaGraph(230, 100, 1.0f, 0.0f, lpImage.GetID("UI/enemy1_UI2"), true, false);

	ScreenFlip();
}

void PlayScene::DrawPlayer(const std::shared_ptr<ControlledPlayer>& player)
{
	if (player->GetisTurnFlag())
	{
		zFlag_ = false;
	}
	else
	{
		zFlag_ = true;
	}

	if (zFlag_)
	{
		player->Draw_();
		player->GetCurrentWeapon()->Draw(player->GetisTurnFlag());
	}
	else
	{
		player->GetCurrentWeapon()->Draw(player->GetisTurnFlag());
		player->Draw_();
	}
}

void PlayScene::Initialize(void)
{
	auto& imageMng = ImageManager::GetInstance();

	currentWeather_ = "Normalsky";

	imageMng.LoadDiv("Normalsky", Vector2I(800, 387), Vector2I(2, 3));
	imageMng.LoadDiv("Thundersky", Vector2I(800, 387), Vector2I(2, 3));

	imageMng.Load("UI/enemy1_UI2");

	lpSound.Load("pistol/fire", true);
	lpSound.Load("sub_machinegun/fire", true);
	lpSound.Load("explosion", false);
	lpSound.Load("bgm", true);

	// �G�S�̂�AI�̊Ǘ��׽
	aiManager_ = std::make_unique<EnemyAIManager>(enemyList_);

	spawner_ = std::make_shared<Spawner>();
	frame_ = 0;
	// ��ڲ԰�ƓG�̎�ނ̖��O
	actorName_ =
	{
		"Player",
		"Pod",
		"Exoskeleton",
		"Roboid",
		"Robo-Soldier",
		"Soldier",
		"Spacenaut"
	};
	zFlag_ = false;

	playerList_.emplace_back(std::make_shared<ControlledPlayer>(Vector2I(200, 0), 0, ActorType::Player));

	auto& app = Application::Instance();
	AddObject(std::make_shared<BackGround>());
	AddObject(std::make_shared<Floor>
		(Vector2I(app.GetViewport().GetSize().x / 2, app.GetViewport().GetSize().y / 2 + 150),
			ObjectType::Floor));

	// �w�i���߼޼�ݾ��
	// �ݽ�׸����߼޼�ݾ�Ă�����������ł����ق�����ׂ�ǉ�����Ƃ��ɂ���Ȃ肢���̂�
	for (auto obj : objList_)
	{
		if (obj->GetType() == ObjectType::BackGround)
		{
			obj->SetPos(Vector2I(app.GetViewport().GetSize().x / 2, app.GetViewport().GetSize().y / 2));
		}
	}

	for (auto player : playerList_)
	{
		lpS_Effect.GetPlayer(player);
	}
}

void PlayScene::AddObject(ObjectPtr object)
{
	objList_.push_back(object);
}