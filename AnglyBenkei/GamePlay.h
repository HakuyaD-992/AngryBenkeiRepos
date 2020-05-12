#pragma once
#include <array>
#include "BaseScene.h"
#include "ANIMATION.h"
#include "AddList.h"
#include "WEAPON.h"
#include "ATTACK_LEVEL.h"


using FileName = std::vector<std::string>;
using WeaponFile = std::vector<FileName>;

// 武器毎の格納配列
using WeaponFrame = std::vector<int>;

struct Actor
{
	// ﾌﾟﾚｲﾔｰの名前
	std::array<std::string, Player_Max> playerName;
	// ｱﾆﾒｰｼｮﾝ名
	std::array<std::string, ANIM_MAX> animationName;
	// ｱﾆﾒｰｼｮﾝの段階別の文字列
	std::array<std::string, LEVEL_MAX> levelName;
	// 1ｱﾆﾒｰｼｮﾝの最大ﾌﾚｰﾑ数
	std::array<WeaponFrame,WEAPON_MAX> frame[ANIM_MAX];
	// 攻撃ｱﾆﾒｰｼｮﾝの段階別の画像枚数
	std::array<WeaponFrame,WEAPON_MAX> attackFrameNum;
	// 1ｱﾆﾒｰｼｮﾝのﾚﾍﾞﾙ総数
	std::array<int, WEAPON_MAX> levelNum[ANIM_MAX];
	// 武器の種類
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
	// 初期化関係関数
	bool Init(void);
	// ﾌﾚｰﾑ初期化関数
	bool InitFrame(const ANIMATION& anim, const WEAPON& weapon,const PLAYER& player);
	// 描画関係関数
	void Draw(void);
	// ﾃﾞﾊﾞｯｸﾞ描画関係関数
	void DebugDraw(void);

	std::array<WeaponFile,WEAPON_MAX> fileName[ANIM_MAX];

	// ｱｸﾀｰ毎の変数
	Actor actor[Player_Max];

	// ﾌﾟﾚｲﾔｰ情報を格納しているﾘｽﾄ
	SharedListPtr playerList;
	// ｱｲﾃﾑ情報を格納しているﾘｽﾄ
	SharedWeaponListPtr itemList;
};

