#pragma once
#include "BaseScene.h"

class Title :
	public BaseScene
{
public:
	Title();
	~Title();
	// ｼｰﾝｱｯﾌﾟﾃﾞｰﾄ
	ScenePtr SceneUpDate(ScenePtr own, const PlayerController& gameCtl);
	// ﾀｲﾄﾙﾛｺﾞのﾎﾟｼﾞｼｮﾝ等の更新
	void TitleLogoUpDate(void);


private:
	// 初期化関係関数
	bool Init(void);
	// 描画関係関数
	void Draw(void);
	// ﾃﾞﾊﾞｯｸﾞ表示関数
	void DebugDraw(void);
	// ﾀｲﾄﾙﾛｺﾞの描画
	void TitleLogoDraw(void);
	// ﾀｲﾄﾙﾛｺﾞのﾎﾟｼﾞｼｮﾝ
	Vector2 titleLogoPos;

	int debugFlag;
};

