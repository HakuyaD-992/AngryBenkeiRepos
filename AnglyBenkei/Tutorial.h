#pragma once
#include "BaseScene.h"
class Tutorial :
	public BaseScene
{
public:
	Tutorial();
	~Tutorial();

	ScenePtr SceneUpDate(ScenePtr own, const PlayerController& gameCtl);

private:
	// �������֌W�֐�
	bool Init(void);
	// �`��֌W�֐�
	void Draw(void);
	// ���ޯ�ޕ`��֌W�֐�
	void DebugDraw(void);
};

