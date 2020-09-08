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

	if (!changeWaveFlag_)
	{
		if (defeatEnemyNum_ >= enemyMaxNuminWave_[static_cast<int>(wave_)])
		{
			changeWaveFlag_ = true;
			wave_ = wave_ + 1;
			defeatEnemyNum_ = 0;
		}
	}

	if (!changeWaveFlag_)
	{
		if (frame_ % 100 == 0)
		{
			if (enemyCountinWave_[static_cast<int>(wave_)] <
				enemyMaxNuminWave_[static_cast<int>(wave_)])
			{
				// ìGÇÃï°êª
				spawner_->MakeClone(enemyList_, playerList_,wave_);
				enemyCountinWave_[static_cast<int>(wave_)]++;

				for (auto enemy : enemyList_)
				{
					lpS_Effect.GetEnemy(enemy);
				}
			}
		}

		for (auto enemy : enemyList_)
		{
			aiManager_->UpDate(enemy);

			// ìGÇÃ±∆“∞ºÆ›ä÷åW
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
			case ActorType::Spacenaut:
				if (enemy->GetCurrentAnimation() == "attack")
				{
					if (frame_ % 10)
					{
						enemy->AddBullet(enemyBullets_);
					}
					else
					{
						enemy->ReadyToShot();
					}
				}
				break;
			case ActorType::Roboid:
			default:
				break;
			}
			// ìGÇ™éÄÇÒÇæÇÁÃﬂ⁄≤‘∞Ç™ìGÇì|ÇµÇΩêîÇâ¡éZ
			if (enemy->GetType() != ActorType::Exoskeleton)
			{
				if (enemy->GetDeleteFlag())
				{
					defeatEnemyNum_++;
				}
			}
		}

		for (auto b : enemyBullets_)
		{
			b->UpDate();
		}
		lpS_Effect.UpDate(EFFECT_TYPE::non);
		enemyList_.remove_if
		([](std::shared_ptr<Enemy>& enemy) {return enemy->GetDeleteFlag(); });

		fps_.Wait();
		frame_++;
	}
	else
	{
		waveStringPos_.x += 3;
		if (waveStringPos_.x >= 350)
		{
			waveStringPos_.x = 350;
			waveNumExRate_ += 0.05f;
			if (waveNumExRate_ >= 1.0f)
			{
				waveNumExRate_ = 1.0f;
				waitFrame_ += 0.01f;
				if (waitFrame_ >= 10.0f)
				{
					waitFrame_ = 0.0f;
					changeWaveFlag_ = false;
				}
			}
		}
	}

	for (auto player : playerList_)
	{
		player->UpDate();
		player->GetCurrentWeapon()->UpDate();
	}
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
	

	if (changeWaveFlag_)
	{
		DrawRotaGraph(waveStringPos_.x, waveStringPos_.y, 1.0f, 0.0f,
			lpImage.GetID("UI/wave"), true, false);

		DrawRotaGraph(waveNumPos_.x, waveNumPos_.y, waveNumExRate_, 0.0f,
			lpImage.GetDivID("UI/wave_num")[static_cast<int>(wave_)], true, false);
		if (waveNumExRate_ >= 1.0f)
		{
			DrawRotaGraph(waveStringPos_.x, waveStringPos_.y + 60, 1.0f, 0.0f,
				lpImage.GetID("UI/untilnext"), true, false);
			DrawRotaGraph(waveNumPos_.x - 80, waveNumPos_.y + 75, waveNumExRate_, 0.0f,
				lpImage.GetDivID("UI/number")[static_cast<int>(10 - waitFrame_)], true, false);
		}
	}
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

	wave_ = Wave::FirstWave;

	enemyCountinWave_ = { 0,0,0 };
	enemyMaxNuminWave_ = { 20,30,1 };

	waveStringPos_ = { -120,50 };
	waveNumPos_ = { 530,50 };
	waveNumExRate_ = 0.0f;
	waitFrame_ = 0.0f;
	defeatEnemyNum_ = 0;


	imageMng.LoadDiv("Normalsky", Vector2I(800, 387), Vector2I(2, 3));
	imageMng.LoadDiv("Thundersky", Vector2I(800, 387), Vector2I(2, 3));
	imageMng.LoadDiv("UI/wave_num", Vector2I(60, 60), Vector2I(3, 1));
	imageMng.LoadDiv("UI/number", Vector2I(22, 40), Vector2I(10, 1));

	imageMng.Load("UI/wave");
	imageMng.Load("UI/untilnext");

	lpSound.Load("pistol/fire", true);
	lpSound.Load("sub_machinegun/fire", true);
	lpSound.Load("explosion", false);
	lpSound.Load("bgm", true);

	// ìGëSëÃÇÃAIÇÃä«óù∏◊Ω
	aiManager_ = std::make_unique<EnemyAIManager>(enemyList_);

	spawner_ = std::make_shared<Spawner>();
	frame_ = 0;
	// Ãﬂ⁄≤‘∞Ç∆ìGÇÃéÌóﬁÇÃñºëO
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

	// îwåiÇÃŒﬂºﬁºÆ›æØƒ
	// ∫›Ωƒ◊∏¿Ç≈ŒﬂºﬁºÆ›æØƒÇ∑ÇÈÇÊÇËÇ‡Ç±Ç±Ç≈ÇµÇΩÇŸÇ§Ç™∂“◊Çí«â¡Ç∑ÇÈÇ∆Ç´Ç…Ç∑ÇÒÇ»ÇËÇ¢Ç≠ÇÃÇ≈
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