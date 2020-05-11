#pragma once
#include <array>

#include "PLAYER.h"

#define PAD_BUTTONMAXNUM 28

using InputArray = std::array<int, PAD_BUTTONMAXNUM>;

struct GamePad
{
	// �ް��߯�ނ̌��݉������Ă����׸�
	InputArray padInputNow;
	// �ް��߯�ނ�1�ڰёO�ɉ������Ă����׸�
	InputArray padInputOld;
	// �ް��߯�ނ𑀍삵�Ă�����ڲ԰
	PLAYER controlledPlayer;
	// ���ݹް��߯�ނ𑀍삵�Ă����߯��
	int playerPad;
};


class GameController
{
public:
	GameController(const PLAYER player);
	~GameController();

	// ���۰װ�̍X�V�֐�
	bool Update(void);

	// �ް��߯�ޗp���͎擾�֐�(�ضް�����̗p)
		/// param@ i: ���͂������݂̎��
	const bool& IsTriggerInputPad(const int& i) const;

	// �ް��߯�ޗp���͎擾�֐�(�ضް�����Ȃ�)
	const bool& IsInputPad(const int& i)const;

	const bool& Init(void);

	// �ް��߯�ޏ��擾�֐�
	const GamePad GetPadInfo(void) const
	{
		return gamePad;
	}
private:
	// �ް��߯�ޏ��
	GamePad gamePad;
};

