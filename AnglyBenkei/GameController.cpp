#include <DxLib.h>

#include "GameController.h"


GameController::GameController(const PLAYER player)
{
	// ���݂̉�������׸ނ̏�����
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
	// ���̉���������U1�ڰёO�̉������ɂ��Ă���
	for (int buttonNum = 0; buttonNum < PAD_BUTTONMAXNUM; buttonNum++)
	{
		gamePad.padInputOld[buttonNum] = gamePad.padInputNow[buttonNum];
	}

	// �ް��߯�ނ̏��X�V
	gamePad.playerPad = GetJoypadInputState((int)gamePad.controlledPlayer + 1);

	// �ް��߯�ނ̓�������݂��������Ă��鎞�͓����׸ނ�true��
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
	// ���݂̉�������׸ނ̏�����
	for (int buttonNum = 0; buttonNum < PAD_BUTTONMAXNUM; buttonNum++)
	{
		gamePad.padInputNow[buttonNum] = false;
		gamePad.padInputOld[buttonNum] = false;
	}
	return true;
}
