#pragma once
#include <mutex>

#include "BaseScene.h"
#include "Vector2.h"
#include "PLAYER.h"

// 今現在のｼｰﾝ状態変数
enum SceneState
{
	// ﾀｲﾄﾙ
	StateTitle,
	// ﾁｭｰﾄﾘｱﾙ
	StateTutorial,
	// ｹﾞｰﾑﾌﾟﾚｲ
	StateGame,
	// ｹﾞｰﾑｵｰﾊﾞｰ
	StateGameOver,
	// ｹﾞｰﾑｸﾘｱ
	StateGameClear,
	// ﾘｻﾞﾙﾄ(ﾗﾝｷﾝｸﾞ登録)
	StateResult,
	StateMax
};

// 画面の横ｻｲｽﾞ
#define Screen_x 960
// 画面の縦ｻｲｽﾞ
#define Screen_y 560

#define lpScene SceneShift::getInstance()


class SceneShift
{
public:
	static void Destroy(void);
	static SceneShift &getInstance(void)
	{
		std::call_once(onceflag, Create);
		return *sceneins;
	}
	void onceRun(void);


	// 画面ｻｲｽﾞ取得関数
	const Vector2 GetScreenSize()
	{
		return Vector2(Screen_x, Screen_y);
	}

	// ｼｰﾝの状態変数取得関数
	SceneState& GetSceneState(void)
	{
		return nowState;
	}


private:
	SceneShift();
	~SceneShift();

	static std::once_flag onceflag;
	static SceneShift* sceneins;

	static void Create(void);

	bool(SceneShift::*s_ptr)(void);

	// DxLib関係の初期化関数
	bool SystemInit(void);

	// ｼｰﾝ毎のﾎﾟｲﾝﾀ
	ScenePtr scenePtr;
	// ｹﾞｰﾑｺﾝﾄﾛｰﾗｰ変数(ｲﾝｽﾀﾝｽ用)
	PlayerController playerController;

	// 現在のｼｰﾝ
	SceneState nowState;
	// 1ﾌﾚｰﾑ前のｼｰﾝ
	SceneState oldState;

};

