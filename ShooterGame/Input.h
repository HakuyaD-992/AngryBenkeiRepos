#pragma once
#include <string>
#include <map>
#include <array>
#include <vector>
#include <DxLib.h>
#include "PLAYER.h"
#include "KeyConfiguration.h"

// 入力機器
enum class Peripheral
{
	Key,
	Pad,
	Max
};

// 今押しているのか、前ﾌﾚｰﾑに押しているのか
enum class TrgFlag
{
	Now,
	Old,
	Max
};

// ｷｰ入力のﾄﾘｶﾞｰﾌﾗｸﾞ
using InputTrg
= std::array<bool, static_cast<int>(TrgFlag::Max)>;
// KeyConfigurationをｷｰにしてTrgﾌﾗｸﾞを取り出す
using PeripheralInfo
= std::map<KeyConfiguration, InputTrg>;

struct Input
{
public:
	void operator()()
	{
		UpDate();
	}
	// 自分の入力情報の取得
	const PeripheralInfo& GetPeriData(void)
	{
		return periData_;
	}
	// 自分の入力装置のﾀｲﾌﾟの取得
	virtual Peripheral GetType(void) = 0;

	virtual bool Setup(const PLAYER& playerNo) = 0;

	// 接続しているﾌﾟﾚｲﾔｰ数取得
	int GetConnectedPlayerNum(void)
	{
		return GetJoypadNum();
	}

private:
	virtual void UpDate(void) = 0;

protected:
	PeripheralInfo periData_;
	PLAYER player_;
};
