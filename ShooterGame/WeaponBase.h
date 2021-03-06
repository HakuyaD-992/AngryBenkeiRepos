#pragma once
#include <string>
#include <map>
#include <list>
#include <memory>
#include <vector>
#include "Geometory.h"
#include "WeaponType.h"
#include "BulletType.h"

// ピストルの弾の最大リロード数
#define PISTOLBULLETNUM 8
// ショットガンの弾の最大リロード数
#define SHOTBULLETNUM 30
// マシンガンの弾の最大リロード数
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

	// 銃弾の追加
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
	// 武器毎のﾘﾛｰﾄﾞ可能なﾀｲﾌﾟ
	BulletType canSetBulletType_;

	std::string name_;
	std::string muzzleFlashName_;
	Vector2I muzzleFlashSize_;
	Vector2I muzzleFlashDivCount_;
	float muzzleFlashAnimationCount_;

	std::string currentAnimation_;
	std::map<std::string,int> animMaxNum_;
	// 今撃ち出している弾の種類
	BulletType bulletType_;

	// 今装備している銃弾の弾ﾘｽﾄ
	std::vector<std::shared_ptr<BulletBase>> bullets_;

	// ｱﾆﾒｰｼｮﾝが終了したﾌﾗｸﾞ
	bool isAnimEnd_;
	float animationCount_;
	// 拡大率
	double exRate_;
	// 回転率
	double rotRate_;
	// 左に向いていたらtrue
	bool isTurnLeft_;

	bool isFire_;

	// 入っている銃弾の数
	int havingBulletNum_;
};

