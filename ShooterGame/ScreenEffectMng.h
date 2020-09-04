#pragma once
#include <map>
#include <string>
#include "ObjectType.h"
#include "Actor.h"
#include "Geometory.h"

#define floor_z 166
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
	void DrawGraph(Vector2I pos,int g_handle,bool trans_flag);
	void DrawRotaGraph(Vector2I pos, float rate, float angle, int g_handle,bool trans_flag, int ReverseXFlag = false, int ReverseYFlag = false);

	const void GetPlayer(shared_ptr<ControlledPlayer> player);
	Vector2I MoveAmountCalculator(ObjectType id);
private:
	ScreenEffectMng();
	~ScreenEffectMng();

	map<string,Vector2I> offset;

	std::shared_ptr<ControlledPlayer> player;
	int frame;

	Vector2I pos;

};

