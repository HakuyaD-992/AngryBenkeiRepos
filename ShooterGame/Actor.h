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
	// (本当はInitializeに書いてもよかったが、Initializeが膨大になってしまうため外に逃がした)
	virtual void RectInitializer(void);
	virtual void Draw(void);
	virtual void Draw_(void) = 0;
	virtual void UpDateAnimation(const std::string& animName);
	// ｱﾆﾒｰｼｮﾝの変更
	void ChangeAnimation(std::string animName);

	const std::string& GetCurrentAnimation(void);

	virtual bool OnFloor(void);

	// ﾀｲﾌﾟ取得関数
	virtual const ActorType& GetType(void)
	{
		return type_;
	}

	// ﾎﾟｼﾞｼｮﾝ取得
	Vector2I& GetPos(void)
	{
		return pos_;
	}
	// ｻｲｽﾞ取得
	const Vector2I& GetSize(void)
	{
		return size_;
	}
	// Zﾎﾟｼﾞｼｮﾝ取得
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

	float& GetAlpha(void)
	{
		return alpha_percent;
	}

	bool& IsJumping(void)
	{
		return isJump_;
	}

	virtual bool& GetOnDamaged(void)
	{
		return onDamaged_;
	}

	// isShot_をtrueにすることで次の弾の生成を可能にする
	virtual void ReadyToShot(void);

	virtual const bool& GetisShot(void)
	{
		return isShot_;
	}

private:
	Vector2I drawPos_;

	float count_;
protected:
	bool deleteFlag_;
	Vector2I pos_;
	// ｽﾋﾟｰﾄﾞ
	Vector2I speed_;
	// 自分のｻｲｽﾞ
	Vector2I size_;
	Vector2I hpPos_;
	// 奥ゆきのｽﾋﾟｰﾄﾞ
	int zSpeed_;
	int z_;
	// ｼﾞｬﾝﾌﾟｽﾋﾟｰﾄﾞ
	int jumpSpeed_;
	float jumpFirstSpeed_;
	float jumpForce_;
	// ﾀﾞﾒｰｼﾞを食らったﾌﾗｸﾞ
	bool onDamaged_;
	// ｼﾞｬﾝﾌﾟﾌﾗｸﾞ
	bool isJump_;
	int drawHpCnt_;
	bool isDrawHp_;

	// 重力
	Gravity* gravity_;
	// 自分のﾀｲﾌﾟ
	ActorType type_;

	// 各ﾌﾟﾚｲﾔｰ、敵の矩形情報
	AnimationRect rect_;

	// 継続時間
	float duration_;
	// ｱﾆﾒｰｼｮﾝが終了したﾌﾗｸﾞ
	bool isAnimEnd_;
	// 攻撃しているかのﾌﾗｸﾞ
	bool isAttack_;
	// ｱﾆﾒｰｼｮﾝの際のｱﾆﾒｰｼｮﾝ名とｱﾆﾒｰｼｮﾝﾌﾚｰﾑ数
	std::map<std::string, int> animationSet_;
	std::string currentAnimation_;
	// ｱﾆﾒｰｼｮﾝの際のｶｳﾝﾀｰ変数
	float animationCount_;
	// ｱﾆﾒｰｼｮﾝをﾙｰﾌﾟするのかのﾌﾗｸﾞ
	std::map<std::string, bool> isLoop_;

	// 自分の向いている方向ﾌﾗｸﾞ
	bool isTurnLeft_;
	// ｱｸﾀｰが動いているﾌﾗｸﾞ
	bool isMove_;
	// 拡大率
	double exRate_;
	// 回転率
	double rotRate_;

	// 各ｱｸﾀｰのHP
	int hp_;

	// 弾を撃つﾌﾗｸﾞ
	bool isShot_;
	// 透過率
	float alpha_percent;
};

