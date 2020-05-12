#pragma once
#include <array>
#include "BaseScene.h"
#include "ANIMATION.h"
#include "AddList.h"
#include "WEAPON.h"
#include "ATTACK_LEVEL.h"


using FileName = std::vector<std::string>;
using WeaponFile = std::vector<FileName>;

// •Ší–ˆ‚ÌŠi”[”z—ñ
using WeaponFrame = std::vector<int>;

struct Actor
{
	// ÌßÚ²Ô°‚Ì–¼‘O
	std::array<std::string, Player_Max> playerName;
	// ±ÆÒ°¼®İ–¼
	std::array<std::string, ANIM_MAX> animationName;
	// ±ÆÒ°¼®İ‚Ì’iŠK•Ê‚Ì•¶š—ñ
	std::array<std::string, LEVEL_MAX> levelName;
	// 1±ÆÒ°¼®İ‚ÌÅ‘åÌÚ°Ñ”
	std::array<WeaponFrame,WEAPON_MAX> frame[ANIM_MAX];
	// UŒ‚±ÆÒ°¼®İ‚Ì’iŠK•Ê‚Ì‰æ‘œ–‡”
	std::array<WeaponFrame,WEAPON_MAX> attackFrameNum;
	// 1±ÆÒ°¼®İ‚ÌÚÍŞÙ‘”
	std::array<int, WEAPON_MAX> levelNum[ANIM_MAX];
	// •Ší‚Ìí—Ş
	std::array<std::string, WEAPON_MAX> weaponString;
};

class GamePlay :
	public BaseScene
{
public:
	GamePlay();
	~GamePlay();

	ScenePtr SceneUpDate(ScenePtr own, const PlayerController& gameCtl);
	void CreateImageFolderPass(const ANIMATION& anim,const WEAPON& weapon,const PLAYER& player);
private:
	// ‰Šú‰»ŠÖŒWŠÖ”
	bool Init(void);
	// ÌÚ°Ñ‰Šú‰»ŠÖ”
	bool InitFrame(const ANIMATION& anim, const WEAPON& weapon,const PLAYER& player);
	// •`‰æŠÖŒWŠÖ”
	void Draw(void);
	// ÃŞÊŞ¯¸Ş•`‰æŠÖŒWŠÖ”
	void DebugDraw(void);

	std::array<WeaponFile,WEAPON_MAX> fileName[ANIM_MAX];

	// ±¸À°–ˆ‚Ì•Ï”
	Actor actor[Player_Max];

	// ÌßÚ²Ô°î•ñ‚ğŠi”[‚µ‚Ä‚¢‚éØ½Ä
	SharedListPtr playerList;
	// ±²ÃÑî•ñ‚ğŠi”[‚µ‚Ä‚¢‚éØ½Ä
	SharedWeaponListPtr itemList;
};

