#pragma once
#include "BaseScene.h"

class Title :
	public BaseScene
{
public:
	Title();
	~Title();
	// ��ݱ����ް�
	ScenePtr SceneUpDate(ScenePtr own, const PlayerController& gameCtl);
	// ����ۺނ��߼޼�ݓ��̍X�V
	void TitleLogoUpDate(void);


private:
	// �������֌W�֐�
	bool Init(void);
	// �`��֌W�֐�
	void Draw(void);
	// ���ޯ�ޕ\���֐�
	void DebugDraw(void);
	// ����ۺނ̕`��
	void TitleLogoDraw(void);
	// ����ۺނ��߼޼��
	Vector2 titleLogoPos;

	int debugFlag;
};

