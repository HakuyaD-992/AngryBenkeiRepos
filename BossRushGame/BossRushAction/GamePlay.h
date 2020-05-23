#pragma once
#include <string>

#include "AnimationLevel.h"
#include "PLAYER.h"
#include "ENEMYTYPE.h"
#include "EnemyAnimation.h"
#include "ANIMATION.h"
#include "BaseScene.h"
#include "AddList.h"

// sprite string
using SpriteString = std::vector<std::vector<std::string>>;

// sprite file
using PlayerSprite = std::array<SpriteString, Animation_Max>;

using EnemyAnimSprite = std::array<std::vector<std::string>,Eanim_Max> ;
using EnemySprite = std::array<EnemyAnimSprite, ETYPE_MAX>;
struct Actor
{
	// player name
	std::string name;
	// level of animation
	std::array<AnimationLevel, Animation_Max> animationLevel;
	// actor's max frame per an animation
	std::array<std::vector<int>,Animation_Max> frameMax;
	// string of player's animation
	std::array<std::string, Animation_Max> animationString;
};



class GamePlay :
	public BaseScene
{
public:
	GamePlay();
	~GamePlay();

	// scene update
	ScenePtr SceneUpDate(ScenePtr own, const PlayerController& gameCtl);

	// initialize gameplayscene
	bool Init(void);
	// draw something in gameplayscene
	void Draw(void);
	// draw debug message
	void DebugDraw(void);
private:
	// create folder path
	void CreateSpriteFolderPath(ANIMATION anim,PLAYER player);
	// create enemy sprite's folder path
	void CreateEnemySpriteFolderPath(EnemyAnimation eAnim, ENEMYTYPE eType);

	void InitPlayerFrame(ANIMATION anim, PLAYER player);
	void InitEnemyFrame(EnemyAnimation eAnim);
	// player's sprite file path name
	PlayerSprite playerSpriteName;
	// enemy's sprite file path name
	EnemySprite enemySpriteName;
	// enemy animation string
	std::array<std::string, Eanim_Max> enemyAnimationString;
	// enemy's type name
	std::array<std::string, ETYPE_MAX> enemyTypeName;
	// enemy's frame max num
	std::array<int,Eanim_Max> enemyFrameMax[ETYPE_MAX];
	// enemy's animation level
	std::array<AnimationLevel, Eanim_Max> enemyAnimationLevelMax;

	// actro's information
	Actor actor[Player_Max];
	// player's list
	SharedPlayerListPtr playerList;
	// enemy's list
	SharedEnemyListPtr enemyList;
};

