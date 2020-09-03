#pragma once
#include "Geometory.h"

#define lpS_Effect ScreenEffectMng::GetInstance()

enum class EFFECT_TYPE
{
	non,
	shake,
	max
};

class ScreenEffectMng
{
public:
	static ScreenEffectMng& GetInstance(void)
	{
		static ScreenEffectMng s_Instance;
		return s_Instance;
	}

	void Init(void);
	void UpDate(EFFECT_TYPE type, int shake_power = 1);
	void DrawGraph(Vector2I pos,int g_handle,bool trans_flag);
	void DrawRotaGraph(Vector2I pos, float rate, float angle, int g_handle,bool trans_flag, int ReverseXFlag = FALSE, int ReverseYFlag = FALSE);
private:
	ScreenEffectMng();
	~ScreenEffectMng();

	Vector2I offset;
	int frame;
};

