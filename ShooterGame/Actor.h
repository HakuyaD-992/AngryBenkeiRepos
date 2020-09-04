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

	virtual bool OnFloor(void);
	virtual bool InFloor(void);

	// ﾎﾟｼﾞｼｮﾝ取得
	const Vector2I& GetPos(void) const
	{
		return pos_;
	}
	// Zﾎﾟｼﾞｼｮﾝ取得
	const int& GetZPos(void) const
	{
		return z_;
	}
	const Vector2I& GetSpeed(void) const
	{
		return speed_;
	}
	const int& GetZSpeed(void) const
	{
		return zSpeed_;
	}
	const bool& GetisTurnFlag(void)
	{
		return isTurnLeft_;
	}
private:
	Vector2I drawPos_;
	float count_;
protected:
	Vector2I pos_;
	// ｽﾋﾟｰﾄﾞ
	Vector2I speed_;
	// 自分のｻｲｽﾞ
	Vector2I size_;
	// 奥ゆきのｽﾋﾟｰﾄﾞ
	int zSpeed_;
	int z_;
	// ｼﾞｬﾝﾌﾟｽﾋﾟｰﾄﾞ
	int jumpSpeed_;
	float jumpFirstSpeed_;
	float jumpForce_;
	// ｼﾞｬﾝﾌﾟﾌﾗｸﾞ
	bool isJump_;

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
	// 敵からの攻撃食らい判定
	bool isDamaged_;

	// ｱﾆﾒｰｼｮﾝの際のｱﾆﾒｰｼｮﾝ名とｱﾆﾒｰｼｮﾝﾌﾚｰﾑ数
	std::map<std::string, int> animationSet_;
	std::string currentAnimation_;
	// ｱﾆﾒｰｼｮﾝの際のｶｳﾝﾀｰ変数
	float animationCount_;
	// ｱﾆﾒｰｼｮﾝをﾙｰﾌﾟするのかのﾌﾗｸﾞ
	std::map<std::string, bool> isLoop_;

	// 各ｱｸﾀｰのHP量
	float hp_;

	// 自分の向いている方向ﾌﾗｸﾞ
	bool isTurnLeft_;
	// ｱｸﾀｰが動いているﾌﾗｸﾞ
	bool isMove_;
	// 拡大率
	double exRate_;
	// 回転率
	double rotRate_;
};

