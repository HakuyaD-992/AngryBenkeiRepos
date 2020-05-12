#pragma once
#include <array>
#include "BaseScene.h"
#include "ANIMATION.h"
#include "AddList.h"
#include "WEAPON.h"
#include "ATTACK_LEVEL.h"


using FileName = std::vector<std::string>;
using WeaponFile = std::vector<FileName>;

// ���했�̊i�[�z��
using WeaponFrame = std::vector<int>;

struct Actor
{
	// ��ڲ԰�̖��O
	std::array<std::string, Player_Max> playerName;
	// ��Ұ��ݖ�
	std::array<std::string, ANIM_MAX> animationName;
	// ��Ұ��݂̒i�K�ʂ̕�����
	std::array<std::string, LEVEL_MAX> levelName;
	// 1��Ұ��݂̍ő��ڰѐ�
	std::array<WeaponFrame,WEAPON_MAX> frame[ANIM_MAX];
	// �U����Ұ��݂̒i�K�ʂ̉摜����
	std::array<WeaponFrame,WEAPON_MAX> attackFrameNum;
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

	std::array<WeaponFile,WEAPON_MAX> fileName[ANIM_MAX];

	// �������̕ϐ�
	Actor actor[Player_Max];

	// ��ڲ԰�����i�[���Ă���ؽ�
	SharedListPtr playerList;
	// ���я����i�[���Ă���ؽ�
	SharedWeaponListPtr itemList;
};

