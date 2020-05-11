#include <DxLib.h>

#include "GameController.h"


GameController::GameController(const PLAYER player)
{
	// ÎŞÀİ‚Ì‰Ÿ‰ºî•ñÌ×¸Ş‚Ì‰Šú‰»
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
	// ¡‚Ì‰Ÿ‰ºî•ñ‚ğˆê’U1ÌÚ°Ñ‘O‚Ì‰Ÿ‰ºî•ñ‚É‚µ‚Ä‚¨‚­
	for (int buttonNum = 0; buttonNum < PAD_BUTTONMAXNUM; buttonNum++)
	{
		gamePad.padInputOld[buttonNum] = gamePad.padInputNow[buttonNum];
	}

	// ¹Ş°ÑÊß¯ÄŞ‚Ìî•ñXV
	gamePad.playerPad = GetJoypadInputState((int)gamePad.controlledPlayer + 1);

	// ¹Ş°ÑÊß¯ÄŞ‚Ì“Á’è‚ÌÎŞÀİ‚ğ‰Ÿ‰º‚µ‚Ä‚¢‚é‚Í“ü—ÍÌ×¸Ş‚ğtrue‚É
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
	// ÎŞÀİ‚Ì‰Ÿ‰ºî•ñÌ×¸Ş‚Ì‰Šú‰»
	for (int buttonNum = 0; buttonNum < PAD_BUTTONMAXNUM; buttonNum++)
	{
		gamePad.padInputNow[buttonNum] = false;
		gamePad.padInputOld[buttonNum] = false;
	}
	return true;
}
