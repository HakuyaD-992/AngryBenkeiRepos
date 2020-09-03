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

PlayScene::PlayScene(SceneController& sCon):
	BaseScene(sCon)
{
	Initialize();
}

PlayScene::~PlayScene()
{
}

void PlayScene::UpDate(const std::vector<std::shared_ptr<Input>>& input)
{
	fps_.Update();

	auto inputData1_ = input[static_cast<int>(PLAYER::ONE)]->GetPeriData();
	auto inputData2_ = input[static_cast<int>(PLAYER::TWO)]->GetPeriData();

	if (frame_ % 1000 == 0)
	{
		spawner_->MakeClone(enemyList_, playerList_);
	}

	for (auto player : playerList_)
	{
		player->UpDate();
		player->GetCurrentWeapon()->UpDate();
	}

	for (auto enemy : enemyList_)
	{
		enemy->UpDate();
	}

	fps_.Wait();
	frame_++;

}

void PlayScene::Draw(void)
{
	ClearDrawScreen();

	DrawFormatString(0, 0, 0xffffff, "GamePlay");


	for (auto obj : objList_)
	{
		obj->Draw();
	}

	for (auto player : playerList_)
	{
		DrawPlayer(player);
	}

	for (auto enemy : enemyList_)
	{
		enemy->Draw();
	}

	fps_.Draw();

	//lpS_Effect.UpDate(EFFECT_TYPE::shake);


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

	spawner_ = std::make_shared<Spawner>();
	frame_ = 0;
	// ÌßÚ²Ô°‚Æ“G‚ÌŽí—Þ‚Ì–¼‘O
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

	AddObject(std::make_shared<Floor>
		(Vector2I(app.GetViewport().GetSize().x / 2, app.GetViewport().GetSize().y / 2 + 150),
			ObjectType::Floor));

}

void PlayScene::AddObject(ObjectPtr object)
{
	objList_.push_back(object);

}