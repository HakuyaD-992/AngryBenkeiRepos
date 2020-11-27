#pragma once
#include <vector>
#include <string>

#include "Geometory.h"
#include "MoneyType.h"

#include "Gravity.h"

class MoneyItem
{
public:
	MoneyItem(const Vector2I& pos,const int& z,MoneyType type);
	~MoneyItem();

	void Update(void);
	bool Initialize(void);
	void Draw(void);

	bool OnFloor(void);

	const Vector2I& GetPos(void)
	{
		return pos_;
	}

	const int& GetZPos(void)
	{
		return z_;
	}

	void Delete(void)
	{
		deleteFlag_ = true;
	}

	const bool& GetDeleteFlag(void) const
	{
		return deleteFlag_;
	}

	const Vector2I& GetSize(void)
	{
		return size_;
	}

	const MoneyType& GetType(void) const
	{
		return type_;
	}

	const int& GetMoneyRate(const MoneyType& type);

private:
	Vector2I pos_;
	Vector2I size_;

	void UpdateAnimation(void);

	int z_;

	MoneyType type_;
	Gravity* gravity_;
	float animationCount_;

	std::vector<int> imageHandle_;
	std::string name_;

	bool deleteFlag_;

	Vector2I dropSpeed_;
	Vector2I dropFirstSpeed_;
	Vector2I dropFirstSpeedBase_;

	Vector2I dropForce_;

	float alphaval_;
	float existLimCount_;
	int flickCount_;
	float exRate_;

	bool eraseFlag_;

	bool dropFlag_;
	// Ãﬂ⁄≤‘∞Ç™éÊìæÇµÇΩç€Ç…ï‚è[â¬î\Ç»èeíeêî
	int bulletNum_;

	int moneyRate_;
};

