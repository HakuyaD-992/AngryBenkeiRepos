#pragma once
#include <mutex>

#include "BaseScene.h"
#include "Vector2.h"
#include "PLAYER.h"

// �����݂̼�ݏ�ԕϐ�
enum SceneState
{
	// ����
	StateTitle,
	// ����ر�
	StateTutorial,
	// �ް���ڲ
	StateGame,
	// �ްѵ��ް
	StateGameOver,
	// �ްѸر
	StateGameClear,
	// ػ���(�ݷݸޓo�^)
	StateResult,
	StateMax
};

// ��ʂ̉�����
#define Screen_x 960
// ��ʂ̏c����
#define Screen_y 560

#define lpScene SceneShift::getInstance()


class SceneShift
{
public:
	static void Destroy(void);
	static SceneShift &getInstance(void)
	{
		std::call_once(onceflag, Create);
		return *sceneins;
	}
	void onceRun(void);


	// ��ʻ��ގ擾�֐�
	const Vector2 GetScreenSize()
	{
		return Vector2(Screen_x, Screen_y);
	}

	// ��݂̏�ԕϐ��擾�֐�
	SceneState& GetSceneState(void)
	{
		return nowState;
	}


private:
	SceneShift();
	~SceneShift();

	static std::once_flag onceflag;
	static SceneShift* sceneins;

	static void Create(void);

	bool(SceneShift::*s_ptr)(void);

	// DxLib�֌W�̏������֐�
	bool SystemInit(void);

	// ��ݖ����߲��
	ScenePtr scenePtr;
	// �ްѺ��۰װ�ϐ�(�ݽ�ݽ�p)
	PlayerController playerController;

	// ���݂̼��
	SceneState nowState;
	// 1�ڰёO�̼��
	SceneState oldState;

};

