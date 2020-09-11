#pragma once
#include <array>
#include <list>
#include <memory>
#include <unordered_map>

#include "BaseScene.h"
#include "ActorType.h"
#include "Fps.h"
#include "Wave.h"
#include "ScreenEffectMng.h"
#include "BulletType.h"

class ControlledPlayer;
class Enemy;
class BulletBase;
class Item;
class EnemyAIManager;
//class ShotBase;
//class Spawner;
class Object;
class Spawner;

using ObjectPtr = std::shared_ptr<Object>;
using ObjectList = std::list<ObjectPtr>;

class PlayScene :
	public BaseScene
{
public:
	PlayScene(SceneController& sCon);
	~PlayScene();

private:
	void UpDate(const std::vector<std::shared_ptr<Input>>& input);
	void Draw(void);
	void DrawPlayer(const std::shared_ptr<ControlledPlayer>& player);
	void Initialize(void);
	void AddObject(ObjectPtr object);
	// 敵がｱｲﾃﾑをドロップする処理
	void DropItem(const Vector2I& pos,const int& z);

	void ChangeWeather(void);
	// 2ﾌﾟﾚｲﾔｰｲﾝｽﾀﾝｽ制御用ﾌﾗｸﾞ
	bool is2PCreate_;
	// 奥行ﾌﾗｸﾞ
	bool zFlag_;

	// 各ﾌﾟﾚｲﾔｰ、敵の名前
	std::array<std::string, static_cast<int>(ActorType::Max)> actorName_;

	std::vector<std::shared_ptr<ControlledPlayer>> playerList_;
	std::list<std::shared_ptr<Enemy>> enemyList_;
	std::unique_ptr<EnemyAIManager> aiManager_;
	// ｱｲﾃﾑ
	std::list<std::shared_ptr<Item>> itemList_;

	// てきの弾(敵のﾀｲﾌﾟによって変化)
	std::vector<std::shared_ptr<BulletBase>> enemyBullets_;

	ObjectList objList_;
	// ﾌﾚｰﾑﾚｰﾄ
	Fps fps_;

	std::array<Vector2I, 2> skyPos_;

	int frame_;
	// ｽﾎﾟｰﾅｰ
	std::shared_ptr<Spawner> spawner_;

	// 現在ﾌﾟﾚｲﾔｰがいる位置の天候
	std::string currentWeather_;
	float weatherAnimationCount_;
	float thunderVol_;
	// 地面を揺らすかのﾀｲﾌﾟ変数
	EFFECT_TYPE shakeEffect_;
	bool isShaking_;
	float shakeTime_;

	float bgmVolume_;

	// 現在ﾌﾟﾚｲﾔｰが存在するwave数
	Wave wave_;
	Vector2I waveStringPos_;
	Vector2I waveNumPos_;
	float waitFrame_;
	float waveNumExRate_;

	bool drawNextWaveFlag_;
	bool changeWaveFlag_;
	bool isNextWave_;
	bool changeVolFlag_;
	bool goNextWave_;
	// ﾌﾟﾚｲﾔｰが倒した敵の数
	int defeatEnemyNum_;

	// 1Waveに対する敵の生成数格納
	// 敵を生成したら加算
	std::array<int, static_cast<int>(Wave::Max)> enemyCountinWave_;
	// 1Wave内の敵の最大生成数
	std::array<int, static_cast<int>(Wave::Max)> enemyMaxNuminWave_;

	bool isPlayBGM_;
	bool createEnemyFlag_;
	// 敵がドロップしたｱｲﾃﾑのﾀｲﾌﾟ
	BulletType dropItemType_;
	// ｱｲﾃﾑドロップの確率
	int droppingRate_;
	// 画面に出現することのできる敵数
	std::array<int, static_cast<int>(Wave::Max)> enemyNum_display_;

	int existEnemyCount_;
	// resultSceneに移行するフラグ
	bool goResult_;
	int goResultAddVal_;
};



