#include <DxLib.h>

#include "GameController.h"


GameController::GameController(const PLAYER player)
{
	// ﾎﾞﾀﾝの押下情報ﾌﾗｸﾞの初期化
	for (int buttonNum = 0; buttonNum < PAD_BUTTONMAXNUM; buttonNum++)
	{
		gamePad.padInputNow[buttonNum] = false;
		gamePad.padInputOld[buttonNum] = false;
	}
	gamePad.controlledPlayer = player;
}

GameController::~GameController()
{
}

bool GameController::Update(void)
{
	// 今の押下情報を一旦1ﾌﾚｰﾑ前の押下情報にしておく
	for (int buttonNum = 0; buttonNum < PAD_BUTTONMAXNUM; buttonNum++)
	{
		gamePad.padInputOld[buttonNum] = gamePad.padInputNow[buttonNum];
	}

	// ｹﾞｰﾑﾊﾟｯﾄﾞの情報更新
	gamePad.playerPad = GetJoypadInputState((int)gamePad.controlledPlayer + 1);

	// ｹﾞｰﾑﾊﾟｯﾄﾞの特定のﾎﾞﾀﾝを押下している時は入力ﾌﾗｸﾞをtrueに
	for (int input = 0; input < PAD_BUTTONMAXNUM; input++)
	{
		if (gamePad.playerPad & (1 << input))
		{
			gamePad.padInputNow[input] = true;
		}
		else
		{
			gamePad.padInputNow[input] = false;
		}
	}
	return true;
}

const bool & GameController::IsTriggerInputPad(const int & i) const
{
	if (gamePad.padInputNow[i] && !gamePad.padInputOld[i])
	{
		return true;
	}
	return false;
}

const bool & GameController::IsInputPad(const int & i) const
{
	if (gamePad.padInputNow[i])
	{
		return true;
	}
	return false;
}

const bool & GameController::Init(void)
{
	// ﾎﾞﾀﾝの押下情報ﾌﾗｸﾞの初期化
	for (int buttonNum = 0; buttonNum < PAD_BUTTONMAXNUM; buttonNum++)
	{
		gamePad.padInputNow[buttonNum] = false;
		gamePad.padInputOld[buttonNum] = false;
	}
	return true;
}
