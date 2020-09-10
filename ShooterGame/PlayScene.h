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
	// “G‚ª±²ÃÑ‚ğƒhƒƒbƒv‚·‚éˆ—
	void DropItem(const Vector2I& pos,const int& z);

	void ChangeWeather(void);
	// 2ÌßÚ²Ô°²İ½Àİ½§Œä—pÌ×¸Ş
	bool is2PCreate_;
	// ‰œsÌ×¸Ş
	bool zFlag_;

	// ŠeÌßÚ²Ô°A“G‚Ì–¼‘O
	std::array<std::string, static_cast<int>(ActorType::Max)> actorName_;

	std::vector<std::shared_ptr<ControlledPlayer>> playerList_;
	std::list<std::shared_ptr<Enemy>> enemyList_;
	std::unique_ptr<EnemyAIManager> aiManager_;
	// ±²ÃÑ
	std::list<std::shared_ptr<Item>> itemList_;

	// ‚Ä‚«‚Ì’e(“G‚ÌÀ²Ìß‚É‚æ‚Á‚Ä•Ï‰»)
	std::vector<std::shared_ptr<BulletBase>> enemyBullets_;

	ObjectList objList_;
	// ÌÚ°ÑÚ°Ä
	Fps fps_;

	std::array<Vector2I, 2> skyPos_;

	int frame_;
	// ½Îß°Å°
	std::shared_ptr<Spawner> spawner_;

	// Œ»İÌßÚ²Ô°‚ª‚¢‚éˆÊ’u‚Ì“VŒó
	std::string currentWeather_;
	float weatherAnimationCount_;
	float thunderVol_;
	// ’n–Ê‚ğ—h‚ç‚·‚©‚ÌÀ²Ìß•Ï”
	EFFECT_TYPE shakeEffect_;
	bool isShaking_;
	float shakeTime_;

	float bgmVolume_;

	// Œ»İÌßÚ²Ô°‚ª‘¶İ‚·‚éwave”
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
	// ÌßÚ²Ô°‚ª“|‚µ‚½“G‚Ì”
	int defeatEnemyNum_;

	// 1Wave‚É‘Î‚·‚é“G‚Ì¶¬”Ši”[
	// “G‚ğ¶¬‚µ‚½‚ç‰ÁZ
	std::array<int, static_cast<int>(Wave::Max)> enemyCountinWave_;
	// 1Wave“à‚Ì“G‚ÌÅ‘å¶¬”
	std::array<int, static_cast<int>(Wave::Max)> enemyMaxNuminWave_;

	bool isPlayBGM_;
	bool createEnemyFlag_;
	// “G‚ªƒhƒƒbƒv‚µ‚½±²ÃÑ‚ÌÀ²Ìß
	BulletType dropItemType_;
	// ±²ÃÑƒhƒƒbƒv‚ÌŠm—¦
	int droppingRate_;
	// ‰æ–Ê‚ÉoŒ»‚·‚é‚±‚Æ‚Ì‚Å‚«‚é“G”
	std::array<int, static_cast<int>(Wave::Max)> enemyNum_display_;

	int existEnemyCount_;
};



