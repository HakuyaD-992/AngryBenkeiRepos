#pragma once
#include <array>

#include "PLAYER.h"

#define PAD_BUTTONMAXNUM 28

using InputArray = std::array<int, PAD_BUTTONMAXNUM>;

struct GamePad
{
	// ｹﾞｰﾑﾊﾟｯﾄﾞの現在押下しているﾌﾗｸﾞ
	InputArray padInputNow;
	// ｹﾞｰﾑﾊﾟｯﾄﾞの1ﾌﾚｰﾑ前に押下しているﾌﾗｸﾞ
	InputArray padInputOld;
	// ｹﾞｰﾑﾊﾟｯﾄﾞを操作しているﾌﾟﾚｲﾔｰ
	PLAYER controlledPlayer;
	// 現在ｹﾞｰﾑﾊﾟｯﾄﾞを操作しているﾊﾟｯﾄﾞ
	int playerPad;
};


class GameController
{
public:
	GameController(const PLAYER player);
	~GameController();

	// ｺﾝﾄﾛｰﾗｰの更新関数
	bool Update(void);

	// ｹﾞｰﾑﾊﾟｯﾄﾞ用入力取得関数(ﾄﾘｶﾞｰ処理採用)
		/// param@ i: 入力したﾎﾞﾀﾝの種類
	const bool& IsTriggerInputPad(const int& i) const;

	// ｹﾞｰﾑﾊﾟｯﾄﾞ用入力取得関数(ﾄﾘｶﾞｰ処理なし)
	const bool& IsInputPad(const int& i)const;

	const bool& Init(void);

	// ｹﾞｰﾑﾊﾟｯﾄﾞ情報取得関数
	const GamePad GetPadInfo(void) const
	{
		return gamePad;
	}
private:
	// ｹﾞｰﾑﾊﾟｯﾄﾞ情報
	GamePad gamePad;
};

