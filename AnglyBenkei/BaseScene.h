#pragma once
#include <memory>
#include <vector>

#include "Vector2.h"
#include "PLAYER.h"

class BaseScene;
class GameController;

// ��ݖ����߲����`
using ScenePtr = std::unique_ptr<BaseScene>;
// ���۰װ���ς�
using PlayerController = std::vector<GameController*>;

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();
	// ��ݑJ�ڊ֐�(���ꂼ��̼�݂��߲����Ԃ��֐�)
	virtual ScenePtr SceneUpDate(ScenePtr own,const PlayerController& gameCtl) = 0;
	// �������֌W�֐�
	virtual bool Init(void) = 0;
	// �`��֐�
	virtual void Draw(void) = 0;
	// ���ޯ�ޕ`��֐�
	virtual void DebugDraw(void) = 0;

private:
	Vector2 ScrSize;

};

