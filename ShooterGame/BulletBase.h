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

	void SetAnimation(std::string animName);

private:

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
};

