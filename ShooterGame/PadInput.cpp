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
						{KeyConfiguration::Fire,PAD_INPUT_6},
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
	padInfo_ = GetJoypadInputState((int)player_);

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
