#include <DxLib.h>

#include "ControlledPlayer.h"
#include "ScreenEffectMng.h"

void ScreenEffectMng::Init(void)
{
	offset["shake"] = Vector2F(0, 0);
	offset["move"] = Vector2F(0, 0);
}

void ScreenEffectMng::UpDate(EFFECT_TYPE type, int shake_power)
{
	switch (type)
	{
	case EFFECT_TYPE::non:
		if (frame > 0)
		{
			frame = 0;
		}
		offset["shake"] = Vector2F(0, 0);
		break;
	case EFFECT_TYPE::shake:
		frame++;
		offset["shake"] = Vector2F(((frame % 3) - 1) * shake_power, ((frame % 3) - 1) * shake_power);
		break;
	default:
		break;
	}
}

void ScreenEffectMng::DrawGraph(Vector2F pos, int g_handle, bool trans_flag)
{
	DxLib::DrawGraph(pos.x + offset["shake"].x, pos.y + offset["shake"].y, g_handle, trans_flag);
}

void ScreenEffectMng::DrawRotaGraph(Vector2F pos, float rate, float angle, int g_handle, bool trans_flag, int ReverseXFlag, int ReverseYFlag)
{
	DrawFormatString(700, 100, 0xffffff, "%d", player->GetZSpeed());
	DxLib::DrawRotaGraph(pos.x + offset["shake"].x, pos.y + offset["shake"].y, rate, angle, g_handle, trans_flag, ReverseXFlag, ReverseYFlag);
}

const void ScreenEffectMng::GetPlayer(std::shared_ptr<ControlledPlayer> player)
{
	this->player = player;
}

Vector2F ScreenEffectMng::MoveAmountCalculator(ObjectType id)
{
	if (id != ObjectType::Floor && player->GetZSpeed() != 0/* && player->GetZPos() -1 >= 450 &&
		player->GetPos().x + 65 <= 800 && player->GetZPos() + 65 <= (450 + 166)*/)
	{
		auto vec = player->GetZSpeed() / -2;
		offset["move"] += Vector2F(0, player->GetZSpeed() + (1.5*vec * static_cast<int>(id)));
	}
	return offset["move"];
}

Vector2F ScreenEffectMng::GetMoveOffset(void)
{
	return offset["move"];
}

ScreenEffectMng::ScreenEffectMng()
{
	Init();
}

ScreenEffectMng::~ScreenEffectMng()
{
}
