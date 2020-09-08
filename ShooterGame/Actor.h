#pragma once
#include <string>
#include <map>
#include "Geometory.h"
#include "ActorType.h"
#include "Gravity.h"
#include "CollisionManager.h"

class Actor
{
public:
	Actor();
	~Actor();

	virtual void UpDate(void) = 0;
	virtual bool Initialize(void);
	// (–{“–‚ÍInitialize‚É‘‚¢‚Ä‚à‚æ‚©‚Á‚½‚ªAInitialize‚ª–c‘å‚É‚È‚Á‚Ä‚µ‚Ü‚¤‚½‚ßŠO‚É“¦‚ª‚µ‚½)
	virtual void RectInitializer(void);
	virtual void Draw(void);
	virtual void Draw_(void) = 0;
	virtual void UpDateAnimation(const std::string& animName);
	// ±ÆÒ°¼®İ‚Ì•ÏX
	void ChangeAnimation(std::string animName);

	const std::string& GetCurrentAnimation(void);

	virtual bool OnFloor(void);

	// À²Ìßæ“¾ŠÖ”
	virtual const ActorType& GetType(void)
	{
		return type_;
	}

	// Îß¼Ş¼®İæ“¾
	Vector2I& GetPos(void)
	{
		return pos_;
	}
	// »²½Şæ“¾
	const Vector2I& GetSize(void)
	{
		return size_;
	}
	// ZÎß¼Ş¼®İæ“¾
	int& GetZPos(void)
	{
		return z_;
	}
	bool& GetisTurnFlag(void)
	{
		return isTurnLeft_;
	}
	Vector2I& GetSpeed(void)
	{
		return speed_;
	}
	int& GetZSpeed(void)
	{
		return zSpeed_;
	}

	bool& GetisAnimEnd(void)
	{
		return isAnimEnd_;
	}

	virtual void Delete(void)
	{
		deleteFlag_ = true;
	}

	virtual const bool& GetDeleteFlag(void)
	{
		return deleteFlag_;
	}

	virtual int& GetHp(void)
	{
		return hp_;
	}

	// isShot_‚ğtrue‚É‚·‚é‚±‚Æ‚ÅŸ‚Ì’e‚Ì¶¬‚ğ‰Â”\‚É‚·‚é
	virtual void ReadyToShot(void);

private:
	Vector2I drawPos_;

	float count_;
protected:
	bool deleteFlag_;
	Vector2I pos_;
	// ½Ëß°ÄŞ
	Vector2I speed_;
	// ©•ª‚Ì»²½Ş
	Vector2I size_;
	// ‰œ‚ä‚«‚Ì½Ëß°ÄŞ
	int zSpeed_;
	int z_;
	// ¼Ş¬İÌß½Ëß°ÄŞ
	int jumpSpeed_;
	float jumpFirstSpeed_;
	float jumpForce_;
	// ¼Ş¬İÌßÌ×¸Ş
	bool isJump_;

	// d—Í
	Gravity* gravity_;
	// ©•ª‚ÌÀ²Ìß
	ActorType type_;

	// ŠeÌßÚ²Ô°A“G‚Ì‹éŒ`î•ñ
	AnimationRect rect_;

	// Œp‘±ŠÔ
	float duration_;
	// ±ÆÒ°¼®İ‚ªI—¹‚µ‚½Ì×¸Ş
	bool isAnimEnd_;
	// UŒ‚‚µ‚Ä‚¢‚é‚©‚ÌÌ×¸Ş
	bool isAttack_;
	// “G‚©‚ç‚ÌUŒ‚H‚ç‚¢”»’è
	bool isDamaged_;

	// ±ÆÒ°¼®İ‚ÌÛ‚Ì±ÆÒ°¼®İ–¼‚Æ±ÆÒ°¼®İÌÚ°Ñ”
	std::map<std::string, int> animationSet_;
	std::string currentAnimation_;
	// ±ÆÒ°¼®İ‚ÌÛ‚Ì¶³İÀ°•Ï”
	float animationCount_;
	// ±ÆÒ°¼®İ‚ğÙ°Ìß‚·‚é‚Ì‚©‚ÌÌ×¸Ş
	std::map<std::string, bool> isLoop_;

	// ©•ª‚ÌŒü‚¢‚Ä‚¢‚é•ûŒüÌ×¸Ş
	bool isTurnLeft_;
	// ±¸À°‚ª“®‚¢‚Ä‚¢‚éÌ×¸Ş
	bool isMove_;
	// Šg‘å—¦
	double exRate_;
	// ‰ñ“]—¦
	double rotRate_;

	// Še±¸À°‚ÌHP
	int hp_;

	// ’e‚ğŒ‚‚ÂÌ×¸Ş
	bool isShot_;
};

