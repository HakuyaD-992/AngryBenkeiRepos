#pragma once
#include <array>
#include <map>
#include "Input.h"


class PadInput :
	public Input
{
public:
	Peripheral GetType(void);
	bool Setup(const PLAYER& playerNo);

	void UpDate(void);
private:
	// Êß¯ÄŞ‚Ì“ü—Íî•ñ
	int padInfo_;
	std::map<KeyConfiguration, int> inputTable_;

};

