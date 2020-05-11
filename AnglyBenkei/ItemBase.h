#pragma once
#include <string>


#include "Gravity.h"
#include "AddList.h"
#include "Vector2.h"
#include "ImageManager.h"
#include "WEAPON.h"
#include "DIRECTION.h"
#include "WeaponInventry.h"

class ItemBase
{
public:
	ItemBase();
	~ItemBase();
	virtual void UpDate(WeakList charaList);

	// 武器描画
	virtual void Draw(void);
	// 武器の初期化関連
	bool Init(std::string imgName,Vector2 size);
	// ｱｲﾃﾑの動き関数
	// 敵が死んだらﾋﾟｮｰﾝと出てくるように
	virtual void Move(WeakList charaList) = 0;
	// ｱｲﾃﾑとﾌﾟﾚｲﾔｰとの距離計算関数
	void CalcDistance(const Vector2& pos);
	// ｱｲﾃﾑとﾌﾟﾚｲﾔｰの当たり判定関数
	virtual bool IsHit(const Vector2& size);

	// 自分の武器ﾀｲﾌﾟ取得関数
	virtual WEAPON& GetWeaponType(void)
	{
		return weaponType;
	}

	// 自身がﾌﾟﾚｲﾔｰから取得されたかのﾌﾗｸﾞ取得関数
	virtual bool& GetisHadbyPlayer(void)
	{
		return isHadbyPlayer;
	}

	// 自身が捨てられたﾌﾗｸﾞの取得関数
	virtual bool& GetisThrowAway(void)
	{
		return isThrowAway;
	}
	// ｲﾝﾍﾞﾝﾄﾘ番号をｾｯﾄ
	void SetInventoryNum(const WeaponInventoryNum& wNum);

	// 武器飛び出しの動き関数
	virtual void JumpFromPlayer(void);

	// 武器ｲﾝﾍﾞﾝﾄﾘに格納されている武器だとその格納されているｲﾝﾍﾞﾝﾄﾘ番号を返す
	WeaponInventoryNum& GetInventoryNum(void)
	{
		return myInventoryNum;
	}
	// ｲﾝﾍﾞﾝﾄﾘ追加ﾌﾗｸﾞ取得関数
	bool& GetAddInventoryFlag(void)
	{
		return addInventoryFlag;
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
	// 武器の画像名
	std::string imageName;
	// 消去ﾌﾗｸﾞ
	bool deleteFlag;

protected:
	// ﾎﾟｼﾞｼｮﾝ
	Vector2 pos;
	// ｻｲｽﾞ
	Vector2 size;
	// 武器がﾌﾟﾚｲﾔｰから飛び出す方向
	DIRECTION jumpDir;
	// 武器ﾀｲﾌﾟ
	WEAPON weaponType;
	// 距離
	Vector2 distance;
	// 重力
	Gravity* gravity;
	// 自身をﾌﾟﾚｲﾔｰから取得されたかのﾌﾗｸﾞ
	bool isHadbyPlayer;
	// 自身をｲﾝﾍﾞﾝﾄﾘに追加するかのﾌﾗｸﾞ
	bool addInventoryFlag;
	// 既に所持済みの格納されている武器ｲﾝﾍﾞﾝﾄﾘ番号を表す
	WeaponInventoryNum myInventoryNum;
	// ﾌﾟﾚｲﾔｰから捨てられたﾌﾗｸﾞ
	bool isThrowAway;
	// 捨てられた時にｱｲﾃﾑがﾋﾟｮｰﾝと飛ぶﾌﾗｸﾞ
	bool isThrowMove;

	// ﾋﾟｮｰﾝと飛び出す初速度
	float startingJumpSpeed;
	// 飛び出し力
	float jumpForce;
	
};

