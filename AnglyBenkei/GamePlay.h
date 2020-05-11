#pragma once
#include <array>
#include "BaseScene.h"
#include "ANIMATION.h"
#include "AddList.h"
#include "WEAPON.h"
#include "ATTACK_LEVEL.h"


using FileName = std::vector<std::string>;

struct Actor
{
	// ��ڲ԰�̖��O
	std::array<std::string, Player_Max> playerName;
	// ��Ұ��ݖ�
	std::array<std::string, ANIM_MAX> animationName;
	// ��Ұ��݂̒i�K�ʂ̕�����
	std::array<std::string, LEVEL_MAX> levelName;
	// 1��Ұ��݂̍ő��ڰѐ�
	std::vector<std::vector<int>> frameMax[ANIM_MAX];
	// 1��Ұ��݂����ّ���
	std::array<int, WEAPON_MAX> levelNum[ANIM_MAX];
	// ����̎��
	std::array<std::string, WEAPON_MAX> weaponString;
};

class GamePlay :
	public BaseScene
{
public:
	GamePlay();
	~GamePlay();

	ScenePtr SceneUpDate(ScenePtr own, const PlayerController& gameCtl);
	void CreateImageFolderPass(const ANIMATION& anim,const WEAPON& weapon,const PLAYER& player);
private:
	// �������֌W�֐�
	bool Init(void);
	// �ڰя������֐�
	bool InitFrame(const ANIMATION& anim, const WEAPON& weapon,const PLAYER& player);
	// �`��֌W�֐�
	void Draw(void);
	// ���ޯ�ޕ`��֌W�֐�
	void DebugDraw(void);

	std::array<FileName, ANIM_MAX> fileName[WEAPON_MAX];


	// �������̕ϐ�
	Actor actor[Player_Max];

	// ��ڲ԰�����i�[���Ă���ؽ�
	SharedListPtr playerList;
	// ���я����i�[���Ă���ؽ�
	SharedWeaponListPtr itemList;
};

