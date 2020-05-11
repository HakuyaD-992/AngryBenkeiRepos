#pragma once
#include <memory>
#include <vector>

#include "Vector2.h"
#include "PLAYER.h"

class BaseScene;
class GameController;

// ¼°İ–ˆ‚ÌÎß²İÀ’è‹`
using ScenePtr = std::unique_ptr<BaseScene>;
// ºİÄÛ°×°‚ğ‰Â•Ï‚É
using PlayerController = std::vector<GameController*>;

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();
	// ¼°İ‘JˆÚŠÖ”(‚»‚ê‚¼‚ê‚Ì¼°İ‚ÌÎß²İÀ‚ğ•Ô‚·ŠÖ”)
	virtual ScenePtr SceneUpDate(ScenePtr own,const PlayerController& gameCtl) = 0;
	// ‰Šú‰»ŠÖŒWŠÖ”
	virtual bool Init(void) = 0;
	// •`‰æŠÖ”
	virtual void Draw(void) = 0;
	// ÃŞÊŞ¯¸Ş•`‰æŠÖ”
	virtual void DebugDraw(void) = 0;

private:
	Vector2 ScrSize;

};

