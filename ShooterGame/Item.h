#pragma once
#include "BulletType.h"
#include "Geometory.h"

class Item
{
public:
	Item(const Vector2I& pos, const int& z, const BulletType& type);
	~Item();
	
	void UpDate(void);
	void Draw(void);
	bool Initialize(void);

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

	const int& GetSize(void)
	{
		return size_;
	}

	const BulletType& GetType(void) const
	{
		return type_;
	}

	const int& GetBulletNum(void) const
	{
		return bulletNum_;
	}

private:
	BulletType type_;
	Vector2I pos_;

	bool deleteFlag_;
	int z_;
	int size_;

	int imageHandle_;

	float dropSpeed_;
	float dropFirstSpeed_;
	float dropForce_;

	float alphaval_;
	float existLimCount_;
	int flickCount_;
	float exRate_;

	bool eraseFlag_;

	bool dropFlag_;
	// Ãﬂ⁄≤‘∞Ç™éÊìæÇµÇΩç€Ç…ï‚è[â¬î\Ç»èeíeêî
	int bulletNum_;
};

