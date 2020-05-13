#pragma once
#include <vector>
#include <string>
#include <array>
#include <map>

#include "Gravity.h"
#include "AddList.h"
#include "Vector2.h"
#include "ANIMATION.h"
#include "DIRECTION.h"
#include "AnimationTB.h"
#include "WEAPON.h"
#include "GamePlay.h"
#include "WeaponInventry.h"
#include "Item_Weapon.h"
#include "Inventory.h"

// ｷｬﾗｸﾀｰのｽﾋﾟｰﾄﾞ
#define Speed 5
// ﾀﾞｯｼｭのﾃﾞﾌｫﾙﾄﾀｲﾑ
#define DashDefTime 20
// 攻撃入力を受け付ける時間（この時間を超えてしまうと待機ﾓｰｼｮﾝに自動的に移行）
#define AttackLimTime 50

class GameController;

class BasePlayer
{
public:
	BasePlayer();
	~BasePlayer();

	virtual void Draw(void);

	void UpDate(const GameController& gameCtl, WeakWeaponList item);
	// ｱﾆﾒｰｼｮﾝ追加関数
	bool AddAnimation(std::string animName, int frame, int interval, bool loop,WEAPON weapon);
	// ｱﾆﾒｰｼｮﾝｾｯﾄ
	bool SetAnimation(std::string animName);
	// ｱﾆﾒｰｼｮﾝ文字列ｾｯﾄの関数
	void SetAnimationString(std::string animString, const ANIMATION& anim);

	// 現在ｱﾆﾒｰｼｮﾝの取得
	std::string GetAnimation(void)
	{
		return animationName;
	}
	// ﾌﾟﾚｲﾔｰのﾎﾟｼﾞｼｮﾝ取得関数
	const Vector2& GetPos(void)
	{
		return pos;
	}
	// 方向取得関数
	const DIRECTION& GetDirection(void)
	{
		return direction;
	}
	// ｱﾆﾒｰｼｮﾝ段階ﾚﾍﾞﾙ取得関数
	ATTACK_LEVEL& GetAnimLevel(ANIMATION anim,WEAPON weapon)
	{
		return animLevel[anim][weapon];
	}

	// 消去系
	bool Getdeleteflag(void)
	{
		return deleteFlag;
	}
	virtual void Delete(void)
	{
		deleteFlag = true;
	}

private:
	virtual void Action(const GameController& gameCtl,WeakWeaponList item) = 0;

	std::vector<std::string> fileName[ANIM_MAX];
	//ｱﾆﾒｰｼｮﾝ関係
	std::map<std::string, int[AnimationTB_Max]> animationTable[WEAPON_MAX];
	//再生するｱﾆﾒｰｼｮﾝ名
	std::string animationName;
	// ｱﾆﾒｰｼｮﾝを制御するｶｳﾝﾄ変数
	int count;

	// 物体消去ﾌﾗｸﾞ
	bool deleteFlag;

protected:
	// ﾎﾟｼﾞｼｮﾝ
	Vector2 pos;
	// 画像ｻｲｽﾞ（多分要らない）
	Vector2 size;
	// 方向
	DIRECTION direction;

	// 重力関係
	Gravity* gravity;

	// ｼﾞｬﾝﾌﾟ関係-------------
	// ｼﾞｬﾝﾌﾟする力
	float jumpForce;
	// ｼﾞｬﾝﾌﾟ時の初速度
	float firstJumpSpeed;
	// ｼﾞｬﾝﾌﾟ中のﾌﾗｸﾞ
	bool isJump;
	//------------------------

	// ﾀﾞｯｼｭ関係--------------
	// ﾀﾞｯｼｭ時間
	int dashTime;
	// ﾀﾞｯｼｭ中のﾌﾗｸﾞ
	bool isDash;
	//------------------------

	// 武器関係-----------
	// 武器ｲﾝﾍﾞﾝﾄﾘに登録する際のｶｳﾝﾄ変数
	WeaponInventoryNum registerNum;
	// 落ちている武器と当たったﾌﾗｸﾞ
	bool isHit;
	// 武器を拾ったﾌﾗｸﾞ
	bool isGet;
	// 不要になった武器を捨てるﾌﾗｸﾞ
	std::array<bool, W_Num_Max> throwAwayFlag;
	// 武器ｲﾝﾍﾞﾝﾄﾘの情報格納用
	Inventory* inventory[W_Num_Max];

	// 今の自分のｱﾆﾒｰｼｮﾝ
	ANIMATION myActionType;
	// 追加する分のｱﾆﾒｰｼｮﾝ毎の名前
	std::string animName[ANIM_MAX];

	// ｶﾞｰﾄﾞしている時間
	int guardTime;
	// 現在攻撃をしている回数
	float attackCount;
	// 攻撃の連携をする際にﾎﾞﾀﾝの入力を受け付ける時間
	// 一定の時間攻撃ﾎﾞﾀﾝを入力していないと待機ﾓｰｼｮﾝに移行させる
	int attackAllowTime;
	// 武器毎に今現在の攻撃段階をｶｳﾝﾄする変数
	std::array<int,WEAPON_MAX> levelCount[ANIM_MAX];
	// 1ﾌﾚｰﾑ前のﾚﾍﾞﾙ
	int oldLevelCount;
	// 攻撃段階
	std::array<std::vector<int>,WEAPON_MAX> attackLevel;
	// 武器毎の最大攻撃回数
	std::array<int, WEAPON_MAX> attackMaxNum;
	// 現在の攻撃ﾓｰｼｮﾝをﾌﾚｰﾑ毎に見た時のﾌﾗｸﾞ
	std::array<bool, WEAPON_MAX> attackFlag;
	// 攻撃ﾎﾞﾀﾝを押していいとなったらtrueを返す
	bool canPushAttackButton;


	// ｱﾆﾒｰｼｮﾝｶｳﾝﾀｰ
	unsigned int animationCount;
	// ｱﾆﾒｰｼｮﾝの段階を表すﾚﾍﾞﾙ
	std::array<ATTACK_LEVEL, WEAPON_MAX> animLevel[ANIM_MAX];
};
