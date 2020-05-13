#pragma once
#include <mutex>
#include <map>
#include <vector>
#include <array>
#include <string>
#include <array>

#include "ANIMATION.h"
#include "ATTACK_LEVEL.h"
#include "Vector2.h"
#include "GamePlay.h"

#define lpImageMng ImageManager::getInstance()

#define FILE_ID(X,Y,Z) (ImageManager::getInstance().GetCombinedID(X,Y,(ATTACK_LEVEL)Z))
#define ENEMYFILE_ID(X,Y) (ImageManager::getInstance().GetCombinedID(X,Y))

// �����^���Łi�摜����ق�ۑ�����p�j
using VecInt = std::vector<int>;
// ��Ұ��ݖ��̕�����p����(��Ұ��݂̖��O��ۑ�����p)
using AnimationString = std::array<std::string, ANIM_MAX>;

class ImageManager
{
public:
	static void Destroy(void);
	static ImageManager &getInstance(void)
	{
		std::call_once(onceflag, Create);
		return *imageIns;
	}
	// ��Ұ��ݖ��̲Ұ��ȰѾ��
	void SetAnimationName(const ANIMATION& anim,const WEAPON& weapon,WeaponFile fileName,ATTACK_LEVEL& level);
	// ��Ұ��ݖ��̕�������
	void SetAnimationString(const std::string animationName, const PLAYER& player, const ANIMATION & anim);
	// ��Ұ��ݖ��̕�����āi�G�p�j
	void SetAnimationString(const ANIMATION& anim);
	// ��Ұ��ݖ��̲Ұ��ȰѾ��(�G�p)
	void SetAnimationName(const ANIMATION& anim,const EnemyType& type,FileName file);
	// 1�����ނ̉摜����َ擾�֐�
	const VecInt& GetID(std::string imageName);
	// 1���̉摜�𕪊����ĉ摜����ق��擾����ۂ̊֐�
	const VecInt& GetID(std::string imageName,Vector2 divSize,Vector2 divCount);
	// 1�����ނ̉摜��A�ԉ摜�Ƃ��ĉ摜����ق��擾����֐�(player�p)
	const VecInt& GetCombinedID(const ANIMATION& anim,const WEAPON& weapon,const int& level);
	// 1�����ނ̉摜��A�ԉ摜�Ƃ��ĉ摜����ق��擾����֐�(enemy�p)
	const VecInt& GetCombinedID(const ANIMATION& anim,const EnemyType& type);
	// ��Ұ��ݖ��擾�֐�
	const AnimationString& GetAnimString(const PLAYER& player)
	{
		return animString[player];
	}

private:
	ImageManager();
	~ImageManager();

	static std::once_flag onceflag;
	static ImageManager* imageIns;

	static void Create(void);

	// �摜�̖��O
	std::string imageName;
	// ��Ұ��ݖ�
	AnimationString animString[Player_Max];
	// ��Ұ��ݖ��̉摜�̖��O(player�p)
	std::array<WeaponFile, WEAPON_MAX> animationImageName[ANIM_MAX];
	// ��Ұ��ݖ��̉摜�̖��O(enemy�p)
	std::array<FileName, ANIM_MAX> enemyImageName[EnemyTypeMax];
	// �摜����ق𕶎���Ŏ��ʂ��邽�߂̺���
	std::map<std::string, VecInt> imageHandleMap;
	// ��ڲ԰�̱�Ұ��ݖ��̉摜����ق��Ұ������قŎ��ʂ��邽�߂̺���
	std::map<ATTACK_LEVEL, VecInt> playerHandleMap[WEAPON_MAX][ANIM_MAX];
	// �G�̱�Ұ��ݖ��̉摜����ق��Ұ��݂Ŏ��ʂ��邽�߂̺���
	std::map<ANIMATION, VecInt> enemyHandleMap[EnemyTypeMax];
};

