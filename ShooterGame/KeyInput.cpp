#include <DxLib.h>
#include "KeyInput.h"

KeyInput::KeyInput()
{
}

KeyInput::~KeyInput()
{
}

void KeyInput::UpDate(void)
{
	GetHitKeyStateAll(&keyData_[0]);

	for (auto config : KeyConfiguration())
	{
		periData_[config][(int)TrgFlag::Old]
			= periData_[config][(int)TrgFlag::Now];
		periData_[config][(int)TrgFlag::Now]
			= keyData_[inputTable_[config]];
	}
}

Peripheral KeyInput::GetType(void)
{
	return Peripheral::Key;
}

bool KeyInput::Setup(const PLAYER& playerNo)
{
	if (playerNo == PLAYER::ONE)
	{
		inputTable_ = {
			{KeyConfiguration::Right,KEY_INPUT_D},
			{KeyConfiguration::Left,KEY_INPUT_A},
			{KeyConfiguration::Up,KEY_INPUT_W},
			{KeyConfiguration::Down,KEY_INPUT_S},
			{KeyConfiguration::Fire,KEY_INPUT_E},
			{KeyConfiguration::ChangeWeapon,KEY_INPUT_Q},
			{KeyConfiguration::Reload,KEY_INPUT_R},
			{KeyConfiguration::Jump,KEY_INPUT_Y},
			{KeyConfiguration::Decision,KEY_INPUT_Z},
			{KeyConfiguration::Reset,KEY_INPUT_X},

		};
	}
	else
	{
		inputTable_ = {
			{KeyConfiguration::Right,KEY_INPUT_RIGHT},
			{KeyConfiguration::Left,KEY_INPUT_LEFT},
			{KeyConfiguration::Up,KEY_INPUT_UP},
			{KeyConfiguration::Down,KEY_INPUT_DOWN},
			{KeyConfiguration::Fire,KEY_INPUT_NUMPAD1},
			{KeyConfiguration::ChangeWeapon,KEY_INPUT_NUMPAD7},
			{KeyConfiguration::Reload,KEY_INPUT_PERIOD},
			{KeyConfiguration::Jump,KEY_INPUT_J},
			{KeyConfiguration::Decision,KEY_INPUT_RETURN},
			{KeyConfiguration::Reset,KEY_INPUT_SPACE},

		};
	}
	player_ = playerNo;
	return true;
}