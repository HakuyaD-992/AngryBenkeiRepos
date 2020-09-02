#pragma once
#include <map>
#include <array>
#include "Input.h"


class KeyInput :
	public Input
{
public:
	KeyInput();
	~KeyInput();

	void UpDate(void);

	Peripheral GetType(void);
	bool Setup(const PLAYER& playerNo);

private:
	std::array<char, 256> keyData_;
	std::map<KeyConfiguration, int> inputTable_;
};

