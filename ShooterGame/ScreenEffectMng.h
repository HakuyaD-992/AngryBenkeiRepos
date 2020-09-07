#pragma once
#include "Geometory.h"

#define lpS_Effect ScreenEffectMng::GetInstance()

enum class EFFECT_TYPE
{
	non,
	shake,
	max
};

enum class LAYER_ID
{
	floor,
	city,
	sky,
	max
};

using namespace std;

class ControlledPlayer;
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
	void DrawGraph(Vector2F pos,int g_handle,bool trans_flag);
	void DrawRotaGraph(Vector2F pos, float rate, float angle, int g_handle,bool trans_flag, int ReverseXFlag = false, int ReverseYFlag = false);

	const void GetPlayer(shared_ptr<ControlledPlayer> player);
	const float& GetMoveOffset(void);
	Vector2F MoveAmountCalculator(ObjectType id);
private:
	ScreenEffectMng();
	~ScreenEffectMng();

	map<string,Vector2F> offset;

	std::shared_ptr<ControlledPlayer> player;
	int frame;

	Vector2I pos;

};

