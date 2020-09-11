#pragma once
#include <string>

#include "Geometory.h"
#include "BulletType.h"

class BulletBase
{
public:
	BulletBase();
	~BulletBase();

	virtual void UpDate(void) = 0;
	virtual void Draw(void) = 0;
	virtual bool Initialize(void) = 0;
	virtual void UpDateAnimation(std::string animName) = 0;

	const Vector2I& GetPos(void) const
	{
		return pos_;
	}
	const Vector2I& GetSize(void) const
	{
		return size_;
	}

	void Delete(void)
	{
		deleteFlag_ = true;
	}

	virtual const bool& GetDeleteFlag(void)
	{
		return deleteFlag_;
	}

	virtual const BulletType& GetType(void) const
	{
		return type_;
	}

	virtual const int& GetZPos(void) const
	{
		return z_;
	}

	virtual const std::string& GetName(void) const
	{
		return bulletName_;
	}

	void SetAnimation(std::string animName);

private:
	bool deleteFlag_;
protected:
	Vector2I pos_;
	Vector2I drawPos_;
	int z_;
	Vector2I size_;
	std::string bulletName_;
	std::string currentAnimation_;

	bool isAnimEnd_;
	float animationCount_;
	bool isMoveLeft_;

	float exRate_;
	float rotRate_;
	// ’e‚Ì½Ëß°ÄÞ
	float speed_;

	BulletType type_;
};

