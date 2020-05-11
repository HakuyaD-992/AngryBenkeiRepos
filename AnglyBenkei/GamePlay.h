#pragma once
#include <array>
#include "BaseScene.h"
#include "ANIMATION.h"
#include "AddList.h"
#include "WEAPON.h"
#include "ATTACK_LEVEL.h"


using FileName = std::vector<std::string>;

struct Actor
{
	// ﾌﾟﾚｲﾔｰの名前
	std::array<std::string, Player_Max> playerName;
	// ｱﾆﾒｰｼｮﾝ名
	std::array<std::string, ANIM_MAX> animationName;
	// ｱﾆﾒｰｼｮﾝの段階別の文字列
	std::array<std::string, LEVEL_MAX> levelName;
	// 1ｱﾆﾒｰｼｮﾝの最大ﾌﾚｰﾑ数
	std::vector<std::vector<int>> frameMax[ANIM_MAX];
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

	std::array<FileName, ANIM_MAX> fileName[WEAPON_MAX];


	// ｱｸﾀｰ毎の変数
	Actor actor[Player_Max];

	// ﾌﾟﾚｲﾔｰ情報を格納しているﾘｽﾄ
	SharedListPtr playerList;
	// ｱｲﾃﾑ情報を格納しているﾘｽﾄ
	SharedWeaponListPtr itemList;
};

