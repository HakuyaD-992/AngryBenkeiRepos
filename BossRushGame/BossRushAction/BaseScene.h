#pragma once
#include <memory>
#include <vector>
#include <array>

#include "Vector2.h"
#include "PLAYER.h"

class BaseScene;
class GameController;

// ¼°Ý–ˆ‚ÌÎß²ÝÀ’è‹`
using ScenePtr = std::unique_ptr<BaseScene>;
// ºÝÄÛ°×°‚ð‰Â•Ï‚É
using PlayerController = std::vector<GameController*>;

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();
	// update scene
	virtual ScenePtr SceneUpDate(ScenePtr own, const PlayerController& gameCtl) = 0;
	// initialize
	virtual bool Init(void) = 0;
	// draw something
	virtual void Draw(void) = 0;
	// draw debug message
	virtual void DebugDraw(void) = 0;

private:

protected:
	// screen size
	Vector2 ScrSize;

};

