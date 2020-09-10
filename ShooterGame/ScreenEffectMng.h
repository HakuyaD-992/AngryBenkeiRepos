#pragma once
#include <map>
#include <vector>
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
class Enemy;
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
	void DrawGraph(Vector2F pos, int g_handle, bool trans_flag);
	void DrawRotaGraph(Vector2F pos, float rate, float angle, int g_handle, bool trans_flag, int ReverseXFlag = false, int ReverseYFlag = false);
	void DrawRotaGraph_AlphaEffect(Vector2F pos, float rate, float angle, int g_handle, bool trans_flag, float percent, int ReverseXFlag = false, int ReverseYFlag = false);
	// èôÅXÇ…ìßâﬂÇµÇƒÇ¢Ç´Ç»Ç™ÇÁï`âÊÇ∑ÇÈ
	void DrawRotaAlphaGraph(const Vector2I& pos, const int& alphaval,const float& exRate, int handle);

	const void GetPlayer(shared_ptr<ControlledPlayer> player);
	const void GetEnemy(shared_ptr<Enemy> player);
	Vector2F MoveAmountCalculator(ObjectType id);
	Vector2F GetMoveOffset(void);


private:
	ScreenEffectMng();
	~ScreenEffectMng();

	map<string, Vector2F> offset;


	std::shared_ptr<ControlledPlayer> player;
	std::shared_ptr<Enemy> enemy;
	int frame;

	Vector2F pos;

	int index_cnt;

};

