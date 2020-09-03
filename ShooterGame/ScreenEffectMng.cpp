#include <DxLib.h>
#include "ScreenEffectMng.h"

void ScreenEffectMng::Init(void)
{
	offset = Vector2I(0, 0);
}

void ScreenEffectMng::UpDate(EFFECT_TYPE type,int shake_power)
{
	switch (type)
	{
	case EFFECT_TYPE::non:
		if (frame > 0)
		{
			frame = 0;
		}
		offset = Vector2I(0, 0);
		break;
	case EFFECT_TYPE::shake:
		frame++;
		offset = Vector2I(((frame % 3) - 1)*shake_power, ((frame % 3) - 1) * shake_power);
		break;
	default:
		break;
	}
}

void ScreenEffectMng::DrawGraph(Vector2I pos, int g_handle,bool trans_flag)
{
	DxLib::DrawGraph(pos.x + offset.x, pos.y + offset.y, g_handle,trans_flag);
}

void ScreenEffectMng::DrawRotaGraph(Vector2I pos,float rate,float angle, int g_handle,bool trans_flag, int ReverseXFlag, int ReverseYFlag)
{
	DxLib::DrawRotaGraph(pos.x + offset.x, pos.y + offset.y,rate,angle, g_handle,trans_flag,ReverseXFlag,ReverseYFlag);
}

ScreenEffectMng::ScreenEffectMng()
{
	Init();
}

ScreenEffectMng::~ScreenEffectMng()
{
}
