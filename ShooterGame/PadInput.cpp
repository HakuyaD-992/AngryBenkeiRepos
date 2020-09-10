#include <DxLib.h>
#include "PadInput.h"

Peripheral PadInput::GetType(void)
{
	return Peripheral::Pad;
}

bool PadInput::Setup(const PLAYER& playerNo)
{
	if (playerNo == PLAYER::ONE)
	{
		inputTable_ = {
						{KeyConfiguration::Right,PAD_INPUT_RIGHT},
						{KeyConfiguration::Left,PAD_INPUT_LEFT},
						{KeyConfiguration::Up,PAD_INPUT_UP},
						{KeyConfiguration::Down,PAD_INPUT_DOWN},
						{KeyConfiguration::Fire,PAD_INPUT_2},
						{KeyConfiguration::ChangeWeapon,PAD_INPUT_6},
						{KeyConfiguration::Jump,PAD_INPUT_7},
						{KeyConfiguration::Decision,PAD_INPUT_2},
						{KeyConfiguration::Reset,PAD_INPUT_10},
		};
	}
	else
	{
		inputTable_ = {
						{KeyConfiguration::Right,PAD_INPUT_RIGHT},
						{KeyConfiguration::Left,PAD_INPUT_LEFT},
						{KeyConfiguration::Up,PAD_INPUT_UP},
						{KeyConfiguration::Down,PAD_INPUT_DOWN},
						{KeyConfiguration::Fire,PAD_INPUT_6},
		};
	}

	player_ = playerNo;
	return true;
}

void PadInput::UpDate(void)
{
	padInfo_ = GetJoypadInputState((int)player_ + 1);

	for (auto config : KeyConfiguration())
	{
		periData_[config][static_cast<int>(TrgFlag::Old)]
			= periData_[config][static_cast<int>(TrgFlag::Now)];

		if (padInfo_ & inputTable_[config])
		{
			periData_[config][static_cast<int>(TrgFlag::Now)]
				= true;
		}
		else
		{
			periData_[config][static_cast<int>(TrgFlag::Now)]
				= false;
		}
	}
}
