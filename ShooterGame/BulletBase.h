#pragma once
#include <string>
#include <map>

#include "Geometory.h"
#include "BulletType.h"

class BulletBase;

class BulletBase
{
public:
	BulletBase();
	~BulletBase();

	virtual void UpDate(void) = 0;
	virtual void Draw(void) = 0;
	virtual bool Initialize(void);
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

	virtual void SetAnimation(std::string animName);

	virtual const bool& GetisShake(void)
	{
		return isShake_;
	}

	virtual void SetHittedBulletType(const BulletType& hitType)
	{
		hittedBulletType_ = hitType;
	}

	const BulletType& GetHittedBulletType(void)
	{
		return hittedBulletType_;
	}

private:
protected:
	Vector2I pos_;
	Vector2I drawPos_;
	bool deleteFlag_;

	int z_;
	Vector2I size_;
	std::string bulletName_;
	std::string currentAnimation_;

	bool isAnimEnd_;
	float animationCount_;
	bool isMoveLeft_;

	float exRate_;
	float rotRate_;
	// íeÇÃΩÀﬂ∞ƒﬁ
	float speed_;

	BulletType type_;

	// ±∆“∞ºÆ›ÇÃç€ÇÃ±∆“∞ºÆ›ñºÇ∆±∆“∞ºÆ›Ã⁄∞—êî
	std::map<std::string, int> animationSet_;
	// ±∆“∞ºÆ›ÇŸ∞ÃﬂÇ∑ÇÈÇÃÇ©ÇÃÃ◊∏ﬁ
	std::map<std::string, bool> isLoop_;

	BulletType hittedBulletType_;

	bool isShake_;
};

