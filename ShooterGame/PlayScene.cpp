#include <DxLib.h>
#include <time.h>
#include "Application.h"
#include "PlayScene.h"
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
#include "Item.h"
#include "EffectManager.h"
#include "SceneController.h"
#include "ResultScene.h"
#include "BulletBase.h"
#include "MoneyItem.h"
#include "GameOver.h"


PlayScene::PlayScene(SceneController& sCon):
	BaseScene(sCon)
{
	Initialize();
	time_start_ = time(NULL);
}

PlayScene::~PlayScene()
{
}

void PlayScene::UpDate(const std::vector<std::shared_ptr<Input>>& input)
{
	time_now_ = time(NULL);
	fps_.Update();

	auto inputData1_ = input[static_cast<int>(PLAYER::ONE)]->GetPeriData();

	// 敵全員倒す
	if (!drawNextWaveFlag_)
	{
		if (defeatEnemyNum_ >= enemyMaxNuminWave_[static_cast<int>(wave_)])
		{
			totalDefeatEnemyNum_ += defeatEnemyNum_;
			defeatEnemyNum_ = 0;
			if (wave_ != Wave::ThirdWave)
			{
				Enemy::ResetEnemyNo();
				drawNextWaveFlag_ = true;
				// wave変更ﾌﾗｸﾞをtrue
				changeVolFlag_ = true;
			}
		}
	}
	lpEffect.UpDate();
	if (!drawNextWaveFlag_)
	{
		if (!goResult_)
		{
			bgmVolume_ += 3;
			if (bgmVolume_ >= 255)
			{
				bgmVolume_ = 255;
			}
			existEnemyCount_ = enemyList_.size();
			if (frame_ % 100 == 0)
			{
				if (enemyCountinWave_[static_cast<int>(wave_)] <
					enemyMaxNuminWave_[static_cast<int>(wave_)])
				{
					if (existEnemyCount_ < enemyNum_display_[static_cast<int>(wave_)])
					{
						// 敵の複製
						spawner_->MakeClone(enemyList_, playerList_, wave_);
						if (enemyList_.back()->GetType() != ActorType::Exoskeleton)
						{
							enemyCountinWave_[static_cast<int>(wave_)]++;
						}
					}
				}
			}
			for (auto enemy : enemyList_)
			{
				aiManager_->UpDate(enemy);

				// 敵のｱﾆﾒｰｼｮﾝ関係
				enemy->Action();
				//dropNum_ = 0;

				// 敵の弾とﾌﾟﾚｲﾔｰの当たり判定
				enemy->CheckHitMyBulletToPlayer(enemyBullets_);

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

				case ActorType::Bigboy:
					if (enemy->GetCurrentAnimation() == "attack")
					{
						enemy->AddBullet(enemyBullets_);
					}

					if (!isShaking_)
					{
						if (existEnemyCount_ < enemyNum_display_[static_cast<int>(wave_)])
						{
							createEnemyFlag_ = true;
						}
						else
						{
							createEnemyFlag_ = false;
						}

						if (enemy->OnFloor())
						{
							// 敵の複製
							spawner_->MakeClone(enemyList_, playerList_, wave_, createEnemyFlag_);
							lpSound.Play("onFloor", DX_PLAYTYPE_BACK);
							isShaking_ = true;
							shakeEffect_ = EFFECT_TYPE::shake;
						}
					}
					else
					{
						if (enemy->IsJumping())
						{
							isShaking_ = false;
						}
					}
					if (enemy->GetCurrentAnimation() == "death")
					{
						if (enemy->GetisAnimEnd())
						{
							goResult_ = true;
							resultFlag_ = true;
						}
					}
					break;
				default:
					break;
				}
				// 敵が死んだらﾌﾟﾚｲﾔｰが敵を倒した数を加算
				if (enemy->GetType() != ActorType::Exoskeleton)
				{
					if (wave_ < Wave::ThirdWave)
					{
						if (enemy->GetDeleteFlag())
						{
							defeatEnemyNum_++;
							existEnemyCount_--;
							if (GetRand(droppingRate_) == 1 ||
								GetRand(droppingRate_) == 2)
							{
								DropItem(enemy->GetPos(), enemy->GetZPos());
							}
						}
					}
					else
					{
						if (enemy->GetDeleteFlag())
						{
							if (enemy->GetType() == ActorType::Bigboy)
							{
								defeatEnemyNum_++;
								existEnemyCount_--;
								goResult_ = true;
								resultFlag_ = true;
							}
							else
							if (GetRand(droppingRate_) == 1 ||
								GetRand(droppingRate_) == 2)
							{
								DropItem(enemy->GetPos(), enemy->GetZPos());
							}
						}
					}
				}
			}

			for (auto b : enemyBullets_)
			{
				b->UpDate();

				if (b->GetisShake())
				{
					shakeEffect_ = EFFECT_TYPE::shake;
					isShaking_ = true;
				}
			}

			if (isShaking_)
			{
				shakeTime_ += 0.3f;
				if (shakeTime_ >= 6.0f)
				{
					shakeEffect_ = EFFECT_TYPE::non;
					shakeTime_ = 0.0f;
				}
			}
			else
			{
				shakeEffect_ = EFFECT_TYPE::non;
				shakeTime_ = 0.0f;
			}

			// effectTypeを変更することで揺らす事が可能
			lpS_Effect.UpDate(shakeEffect_, 5);

			fps_.Wait();
			frame_++;
		}
	}
	else
	{
		if (changeVolFlag_)
		{
			bgmVolume_ -= 0.4f;
			if (bgmVolume_ <= 0)
			{
				bgmVolume_ = 0;
				lpSound.Stop("bgm_wave" + std::to_string(static_cast<int>(wave_)));
				changeVolFlag_ = false;
				changeWaveFlag_ = true;
			}
		}
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
					waveNumExRate_ = 0.0f;
					waveStringPos_.x = -120;
					// 描画ﾌﾗｸﾞをfalse
					drawNextWaveFlag_ = false;
					// BGMﾌﾟﾚｲﾌﾗｸﾞをtrue
					isPlayBGM_ = true;
				}
			}
		}
	}
	if (changeWaveFlag_)
	{
		wave_ = wave_ + 1;
		ChangeWeather();
		changeWaveFlag_ = false;
	}

	lpSound.ChangeVolume("bgm_wave" + std::to_string(static_cast<int>(wave_+1)),
		bgmVolume_);

	if (isPlayBGM_)
	{
		changeWaveFlag_ = false;
		isNextWave_ = false;
		isPlayBGM_ = false;
		goNextWave_ = false;
		lpSound.Play("bgm_wave" + std::to_string(static_cast<int>(wave_+1)), DX_PLAYTYPE_LOOP);
		isPlayBGM_ = false;
	}

	for (auto item : itemList_)
	{
		item->UpDate();
	}

	//for (auto money : moneyList_)
	//{
	//	money->Update();
	//}

	for (auto player : playerList_)
	{
		if (shakeEffect_ != EFFECT_TYPE::shake)
		{
			player->UpDate();
		}
		int num = 0;
		player->GetCurrentWeapon()->UpDate();
		if (player->GetDeleteFlag())
		{
			gameOverFlag_ = true;
			goResult_ = true;
			totalUseBullet_ = player->GetUseBullet();
		}
		totalUseBullet_ = player->GetUseBullet();
		for (auto weapon : player->GetWeapons())
		{
			num = weapon->GetHavingBulletNum();
		}
		if (num <= 0)
		{
			goResult_ = true;
			gameOverFlag_ = true;
		}
	}


	playerList_.erase(std::remove_if(playerList_.begin(),
		playerList_.end(),
		[&](std::shared_ptr<ControlledPlayer>& player) {
			return player->GetDeleteFlag();
		}), playerList_.end());

	enemyList_.remove_if
	([](std::shared_ptr<Enemy>& enemy) {return enemy->GetDeleteFlag(); });

	itemList_.remove_if
	([](std::shared_ptr<Item>& item) {return item->GetDeleteFlag(); });

	/*moneyList_.remove_if
	([](std::shared_ptr<MoneyItem>& money) {return money->GetDeleteFlag(); });*/

	// 敵の弾の消去
	enemyBullets_.erase(std::remove_if(enemyBullets_.begin(),
		enemyBullets_.end(),
		[&](std::shared_ptr<BulletBase>& bullet) {
			return bullet->GetDeleteFlag();
		}), enemyBullets_.end());

	if (goResult_)
	{
		goResultAddVal_--;
		if (goResultAddVal_ <= 0)
		{
			goResultAddVal_ = 0;
			// 全ての音楽を止める
			lpSound.StopAll();
			lpSound.Stop("bgm_wave" + std::to_string(static_cast<int>(wave_ + 1))); 
			spendTime_ = time_now_ - time_start_;
			if (resultFlag_)
			{
				sceneCtl_.ChangeScene(std::make_shared<ResultScene>(sceneCtl_, totalUseBullet_, spendTime_,totalDefeatEnemyNum_));
			}

			if (gameOverFlag_)
			{
				sceneCtl_.ChangeScene(std::make_shared<GameOver>(sceneCtl_));
			}
		}
	}

	if (currentWeather_ == "Thundersky")
	{
		weatherAnimationCount_ += 0.05f;
		if (weatherAnimationCount_ >= 5)
		{
			weatherAnimationCount_ = 0.0f;
		}
	}
	else
	{
		for (auto& sky : skyPos_)
		{
			sky.x++;
			if (sky.x >= 1200)
			{
				sky.x = -400;
			}
		}
	}
}

void PlayScene::Draw(void)
{
	auto& app = Application::Instance();
	auto scr = app.GetViewport().GetSize();

	ClearDrawScreen();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,goResultAddVal_);
	DrawRotaGraph(skyPos_[0].x,skyPos_[0].y,
		1.0f, 0.0f,
		lpImage.GetDivID(currentWeather_)[weatherAnimationCount_], true);
	if (currentWeather_ == "Normalsky")
	{
		DrawRotaGraph(skyPos_[1].x, skyPos_[1].y,
			1.0f, 0.0f,
			lpImage.GetDivID(currentWeather_)[weatherAnimationCount_], true);
	}


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
	}

	for (auto item : itemList_)
	{
		item->Draw();
	}

	/*for (auto money : moneyList_)
	{
		money->Draw();
	}*/

	if (drawNextWaveFlag_)
	{
		DrawRotaGraph(waveStringPos_.x, waveStringPos_.y, 1.0f, 0.0f,
			lpImage.GetID("UI/wave"), true, false);

		DrawRotaGraph(waveNumPos_.x,waveNumPos_.y, waveNumExRate_, 0.0f,
			lpImage.GetDivID("UI/wave_num")[static_cast<int>(wave_)], true, false);
		if (waveNumExRate_ >= 1.0f)
		{
			DrawRotaGraph(waveStringPos_.x, waveStringPos_.y + 60, 1.0f, 0.0f,
				lpImage.GetID("UI/untilnext"), true, false);
			DrawRotaGraph(waveNumPos_.x-80, waveNumPos_.y + 75, waveNumExRate_, 0.0f,
				lpImage.GetDivID("UI/number")[static_cast<int>(10 - waitFrame_)], true, false);
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawRotaGraph(existEnemyUIPos_.x, existEnemyUIPos_.y,
		1.0f, 0.0f,
		lpImage.GetID("UI/exist"), true, false);

	DrawRotaGraph(existEnemyUIPos_.x + 80, existEnemyUIPos_.y,
		1.0f, 0.0f,
		lpImage.GetDivID("UI/number")
		[(enemyMaxNuminWave_[static_cast<int>(wave_)]-defeatEnemyNum_)/10], true, false);
	DrawRotaGraph(existEnemyUIPos_.x + 100, existEnemyUIPos_.y,
		1.0f, 0.0f,
		lpImage.GetDivID("UI/number")
		[(enemyMaxNuminWave_[static_cast<int>(wave_)] - defeatEnemyNum_) % 10], true, false);
	//fps_.Draw();
	//DrawFormatString(0, 0, 0xffffff, "%d秒", time_now_ - time_start_);
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
	auto& app = Application::Instance();

	auto scr = app.GetViewport().GetSize();
	auto& imageMng = ImageManager::GetInstance();

	wave_ = Wave::FirstWave;

	shakeEffect_ = EFFECT_TYPE::non;
	shakeTime_ = 0.0f;
	isShaking_ = false;

	enemyCountinWave_ = { 0,0,0 };
	enemyMaxNuminWave_ = { 30,30,1 };
	enemyNum_display_ = {5,6,2};
	existEnemyCount_ = 0;
	totalUseBullet_ = 0;
	totalDefeatEnemyNum_ = 0;

	time_start_ = 0;
	time_now_ = 0;
	spendTime_ = 0;

	waveStringPos_ = { -120,50 };
	waveNumPos_ = { 530,50 };
	skyPos_[0] = { scr.x / 2, scr.y / 2 - 106 };
	skyPos_[1] = { -scr.x / 2, scr.y / 2 - 106 };
	waveNumExRate_ = 0.0f;
	waitFrame_ = 0.0f;
	bgmVolume_ = 0.0f;
	defeatEnemyNum_ = 0;
	droppingRate_ = 5;
	resultFlag_ = false;

	//dropNum_ = 0;

	dropItemType_ = BulletType::Max;

	isPlayBGM_ = false;
	isNextWave_ = false;
	changeVolFlag_ = false;
	goNextWave_ = false;
	drawNextWaveFlag_ = true;
	createEnemyFlag_ = false;
	//moneyScatteringDirection_ = false;
	currentWeather_ = "Normalsky";
	weatherAnimationCount_ = 0.0f;

	gameOverFlag_ = false;

	changeWaveFlag_ = false;
	goResult_ = false;
	goResultAddVal_ = 255;

	existEnemyUIPos_ = { 570,100 };

	// 敵全体のAIの管理ｸﾗｽ
	aiManager_ = std::make_unique<EnemyAIManager>(enemyList_);

	spawner_ = std::make_shared<Spawner>();
	frame_ = 0;
	// ﾌﾟﾚｲﾔｰと敵の種類の名前
	actorName_ =
	{
		"Player",
		"Pod",
		"Exoskeleton",
		"Spacenaut",
		"Bigboy"
	};
	zFlag_ = false;

	playerList_.emplace_back(std::make_shared<ControlledPlayer>(Vector2I(200, 0), 0, ActorType::Player,itemList_/*,moneyList_*/));

	AddObject(std::make_shared<BackGround>(playerList_.front()));
	AddObject(std::make_shared<Floor>
		(Vector2I(app.GetViewport().GetSize().x / 2, app.GetViewport().GetSize().y / 2 + 150),
			ObjectType::Floor, playerList_.front()));

	// 背景のﾎﾟｼﾞｼｮﾝｾｯﾄ
	// ｺﾝｽﾄﾗｸﾀでﾎﾟｼﾞｼｮﾝｾｯﾄするよりもここでしたほうがｶﾒﾗを追加するときにすんなりいくので
	for (auto obj : objList_)
	{
		if (obj->GetType() == ObjectType::BackGround)
		{
			obj->SetPos(Vector2I(app.GetViewport().GetSize().x / 2, app.GetViewport().GetSize().y / 2));
		}
	}

}

void PlayScene::AddObject(ObjectPtr object)
{
	objList_.push_back(object);
}

void PlayScene::DropItem(const Vector2I& pos, const int& z)
{
	dropItemType_ = (BulletType)GetRand(static_cast<int>(BulletType::MachineBullet));
	itemList_.emplace_back(std::make_shared<Item>(pos, z, dropItemType_));
}

//void PlayScene::DropMoney(const Vector2I& pos, const int& z)
//{
//	dropMoneyType_ = (MoneyType)GetRand(static_cast<int>(MoneyType::Red));
//	moneyList_.emplace_back(std::make_shared<MoneyItem>(pos, z, dropMoneyType_));
//}

void PlayScene::ChangeWeather(void)
{
	auto& app = Application::Instance();
	switch (wave_)
	{
	case Wave::FirstWave:
	case Wave::SecondWave:
		currentWeather_ = "Normalsky";

		break;
	case Wave::ThirdWave:
		// 画像のﾎﾟｼﾞｼｮﾝの初期化
		skyPos_[0] = { app.GetViewport().GetSize().x/2,
			app.GetViewport().GetSize().y / 2 - 106 };
		skyPos_[1] = { -app.GetViewport().GetSize().x / 2,
			app.GetViewport().GetSize().y / 2 - 106 };
		currentWeather_ = "Thundersky";
		lpSound.Play("thunder", DX_PLAYTYPE_BACK);
		break;
	case Wave::Max:
		break;
	default:
		break;
	}
}
