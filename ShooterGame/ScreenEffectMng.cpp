#include <DxLib.h>
#include "ScreenEffectMng.h"

void ScreenEffectMng::Init(void)
{
	offset["shake"] = Vector2I(0, 0);
	offset["move"] = Vector2I(0, 0);
}

void ScreenEffectMng::UpDate(EFFECT_TYPE type, int player_pos, int player_speed, int shake_power)
{
	this->player_pos = player_pos;
	this->player_speed = player_speed;

	switch (type)
	{
	case EFFECT_TYPE::non:
		if (frame > 0)
		{
			frame = 0;
		}
		offset["shake"] = Vector2I(0, 0);
		break;
	case EFFECT_TYPE::shake:
		frame++;
		offset["shake"] = Vector2I(((frame % 3) - 1)*shake_power, ((frame % 3) - 1) * shake_power);
		break;
	default:
		break;
	}
}

void ScreenEffectMng::DrawGraph(Vector2I pos, int g_handle,bool trans_flag)
{
	DxLib::DrawGraph(pos.x + offset["shake"].x, pos.y + offset["shake"].y, g_handle,trans_flag);
}

void ScreenEffectMng::DrawRotaGraph(Vector2I pos,float rate,float angle, int g_handle,bool trans_flag, int ReverseXFlag, int ReverseYFlag)
{
	DxLib::DrawRotaGraph(pos.x + offset["shake"].x, pos.y + offset["shake"].y,rate,angle, g_handle,trans_flag,ReverseXFlag,ReverseYFlag);
}

Vector2I ScreenEffectMng::MoveAmountCalculator(LAYER_ID id)
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
