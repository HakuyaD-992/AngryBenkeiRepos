#pragma once
#include <string>
#include <map>
#include <list>
#include <memory>
#include <vector>
#include "Geometory.h"
#include "WeaponType.h"
#include "BulletType.h"

// ƒsƒXƒgƒ‹‚Ì’e‚ÌÅ‘åƒŠƒ[ƒh”
#define PISTOLBULLETNUM 8
// ƒVƒ‡ƒbƒgƒKƒ“‚Ì’e‚ÌÅ‘åƒŠƒ[ƒh”
#define SHOTBULLETNUM 30
// ƒ}ƒVƒ“ƒKƒ“‚Ì’e‚ÌÅ‘åƒŠƒ[ƒh”
#define MACHINEBULLETNUM 300

class BulletBase;

class WeaponBase
{
public:
	WeaponBase();
	~WeaponBase();

	virtual void UpDate(void) = 0;
	virtual bool Initialize(void);
	virtual void UpDateAnimation(std::string animName) = 0;

	virtual void Draw(const bool& turnFlag);

	void SetPos(const Vector2I& pos,int z);
	void SetAnimation(std::string animName);

	const WeaponType& GetType(void)
	{
		return type_;
	}

	const std::string& GetWeaponName(void)
	{
		return name_;
	}

	// e’e‚Ì’Ç‰Á
	void AddBullet(void);

	std::vector<std::shared_ptr<BulletBase>>& GetBullets(void)
	{
		return bullets_;
	}

	const std::string& GetAnimation(void)
	{
		return currentAnimation_;
	}

	int& GetHavingBulletNum(void)
	{
		return havingBulletNum_;
	}

	const BulletType& GetcanSetBulletType(void)
	{
		return canSetBulletType_;
	}

private:

	Vector2I drawPos_;
	Vector2I muzzleFlashPos_;
protected:
	Vector2I pos_;
	int z_;
	WeaponType type_;
	// •Ší–ˆ‚ÌØÛ°ÄŞ‰Â”\‚ÈÀ²Ìß
	BulletType canSetBulletType_;

	std::string name_;
	std::string muzzleFlashName_;
	Vector2I muzzleFlashSize_;
	Vector2I muzzleFlashDivCount_;
	float muzzleFlashAnimationCount_;

	std::string currentAnimation_;
	std::map<std::string,int> animMaxNum_;
	// ¡Œ‚‚¿o‚µ‚Ä‚¢‚é’e‚Ìí—Ş
	BulletType bulletType_;

	// ¡‘•”õ‚µ‚Ä‚¢‚ée’e‚Ì’eØ½Ä
	std::vector<std::shared_ptr<BulletBase>> bullets_;

	// ±ÆÒ°¼®İ‚ªI—¹‚µ‚½Ì×¸Ş
	bool isAnimEnd_;
	float animationCount_;
	// Šg‘å—¦
	double exRate_;
	// ‰ñ“]—¦
	double rotRate_;
	// ¶‚ÉŒü‚¢‚Ä‚¢‚½‚çtrue
	bool isTurnLeft_;

	bool isFire_;

	// “ü‚Á‚Ä‚¢‚ée’e‚Ì”
	int havingBulletNum_;
};

