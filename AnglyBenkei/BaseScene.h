#pragma once
#include <memory>
#include <vector>

#include "Vector2.h"
#include "PLAYER.h"

class BaseScene;
class GameController;

// ｼｰﾝ毎のﾎﾟｲﾝﾀ定義
using ScenePtr = std::unique_ptr<BaseScene>;
// ｺﾝﾄﾛｰﾗｰを可変に
using PlayerController = std::vector<GameController*>;

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();
	// ｼｰﾝ遷移関数(それぞれのｼｰﾝのﾎﾟｲﾝﾀを返す関数)
	virtual ScenePtr SceneUpDate(ScenePtr own,const PlayerController& gameCtl) = 0;
	// 初期化関係関数
	virtual bool Init(void) = 0;
	// 描画関数
	virtual void Draw(void) = 0;
	// ﾃﾞﾊﾞｯｸﾞ描画関数
	virtual void DebugDraw(void) = 0;

private:
	Vector2 ScrSize;

};

