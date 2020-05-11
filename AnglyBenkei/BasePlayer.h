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
#include "WEAPON.h"
#include "GamePlay.h"
#include "WeaponInventry.h"
#include "Item_Weapon.h"
#include "Inventory.h"

// ·¬×¸À°‚Ì½Ëß°ÄŞ
#define Speed 5
// ÀŞ¯¼­‚ÌÃŞÌ«ÙÄÀ²Ñ
#define DashDefTime 20
// UŒ‚“ü—Í‚ğó‚¯•t‚¯‚éŠÔi‚±‚ÌŠÔ‚ğ’´‚¦‚Ä‚µ‚Ü‚¤‚Æ‘Ò‹@Ó°¼®İ‚É©“®“I‚ÉˆÚsj
#define AttackLimTime 50

class GameController;

// ±ÆÒ°¼®İ‚Ìí—Ş•ÊÃ°ÌŞÙ
enum AnimationTable
{
	Animation_TB_Start,
	Animation_TB_Frame,
	Animation_TB_Interval,
	Animation_TB_Loop,
	AnimationTB_Max
};


class BasePlayer
{
public:
	BasePlayer();
	~BasePlayer();

	virtual void Draw(void);

	void UpDate(const GameController& gameCtl, WeakWeaponList item);
	// ±ÆÒ°¼®İ’Ç‰ÁŠÖ”
	bool AddAnimation(std::string animName, int frame, int interval, bool loop,WEAPON weapon);
	// ±ÆÒ°¼®İ¾¯Ä
	bool SetAnimation(std::string animName);
	// ±ÆÒ°¼®İ•¶š—ñ¾¯Ä‚ÌŠÖ”
	void SetAnimationString(std::string animString, const ANIMATION& anim);

	// Œ»İ±ÆÒ°¼®İ‚Ìæ“¾
	std::string GetAnimation(void)
	{
		return animationName;
	}
	// ÌßÚ²Ô°‚ÌÎß¼Ş¼®İæ“¾ŠÖ”
	const Vector2& GetPos(void)
	{
		return pos;
	}
	// •ûŒüæ“¾ŠÖ”
	const DIRECTION& GetDirection(void)
	{
		return direction;
	}

	// Á‹Œn
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
	//±ÆÒ°¼®İŠÖŒW
	std::map<std::string, int[AnimationTB_Max]> animationTable[WEAPON_MAX];
	//Ä¶‚·‚é±ÆÒ°¼®İ–¼
	std::string animationName;

	// •¨‘ÌÁ‹Ì×¸Ş
	bool deleteFlag;

protected:
	// Îß¼Ş¼®İ
	Vector2 pos;
	// ‰æ‘œ»²½Şi‘½•ª—v‚ç‚È‚¢j
	Vector2 size;
	// •ûŒü
	DIRECTION direction;

	// d—ÍŠÖŒW
	Gravity* gravity;

	// ¼Ş¬İÌßŠÖŒW-------------
	// ¼Ş¬İÌß‚·‚é—Í
	float jumpForce;
	// ¼Ş¬İÌß‚Ì‰‘¬“x
	float firstJumpSpeed;
	// ¼Ş¬İÌß’†‚ÌÌ×¸Ş
	bool isJump;
	//------------------------

	// ÀŞ¯¼­ŠÖŒW--------------
	// ÀŞ¯¼­ŠÔ
	int dashTime;
	// ÀŞ¯¼­’†‚ÌÌ×¸Ş
	bool isDash;
	//------------------------

	// •ŠíŠÖŒW-----------
	// •Ší²İÍŞİÄØ‚É“o˜^‚·‚éÛ‚Ì¶³İÄ•Ï”
	WeaponInventoryNum registerNum;
	// —‚¿‚Ä‚¢‚é•Ší‚Æ“–‚½‚Á‚½Ì×¸Ş
	bool isHit;
	// •Ší‚ğE‚Á‚½Ì×¸Ş
	bool isGet;
	// •s—v‚É‚È‚Á‚½•Ší‚ğÌ‚Ä‚éÌ×¸Ş
	std::array<bool, W_Num_Max> throwAwayFlag;
	// •Ší²İÍŞİÄØ‚Ìî•ñŠi”[—p
	Inventory* inventory[W_Num_Max];

	// ¡‚Ì©•ª‚Ì±ÆÒ°¼®İ
	ANIMATION myActionType;
	// ’Ç‰Á‚·‚é•ª‚Ì±ÆÒ°¼®İ–ˆ‚Ì–¼‘O
	std::string animName[ANIM_MAX];

	// ¶Ş°ÄŞ‚µ‚Ä‚¢‚éŠÔ
	int guardTime;
	// Œ»İUŒ‚‚ğ‚µ‚Ä‚¢‚é‰ñ”
	float attackCount;
	// UŒ‚‚Ì˜AŒg‚ğ‚·‚éÛ‚ÉÎŞÀİ‚Ì“ü—Í‚ğó‚¯•t‚¯‚éŠÔ
	// ˆê’è‚ÌŠÔUŒ‚ÎŞÀİ‚ğ“ü—Í‚µ‚Ä‚¢‚È‚¢‚Æ‘Ò‹@Ó°¼®İ‚ÉˆÚs‚³‚¹‚é
	int attackAllowTime;
	// •Ší–ˆ‚É¡Œ»İ‚ÌUŒ‚’iŠK‚ğ¶³İÄ‚·‚é•Ï”
	std::array<int, WEAPON_MAX> attackLevelCount;
	// UŒ‚’iŠK
	std::array<std::vector<int>,WEAPON_MAX> attackLevel;
	// •Ší–ˆ‚ÌÅ‘åUŒ‚‰ñ”
	std::array<int, WEAPON_MAX> attackMaxNum;
	// Œ»İ‚ÌUŒ‚Ó°¼®İ‚ğÌÚ°Ñ–ˆ‚ÉŒ©‚½‚ÌÌ×¸Ş
	std::array<bool, WEAPON_MAX> attackFlag;

	// ±ÆÒ°¼®İ¶³İÀ°
	unsigned int animationCount;
};
