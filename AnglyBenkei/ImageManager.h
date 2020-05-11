#pragma once
#include <mutex>
#include <map>
#include <vector>
#include <array>
#include <string>
#include <array>

#include "ANIMATION.h"
#include "Vector2.h"
#include "GamePlay.h"

#define lpImageMng ImageManager::getInstance()

#define FILE_ID(X,Y) (ImageManager::getInstance().GetCombinedID(X,Y))

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
	void SetAnimationName(const ANIMATION& anim,const WEAPON& weapon,FileName fileName);
	// ��Ұ��ݖ��̕�������
	void SetAnimationString(const Actor& actor,const ANIMATION& anim);
	// 1�����ނ̉摜����َ擾�֐�
	const VecInt& GetID(std::string imageName);
	// 1���̉摜�𕪊����ĉ摜����ق��擾����ۂ̊֐�
	const VecInt& GetID(std::string imageName,Vector2 divSize,Vector2 divCount);
	// 1�����ނ̉摜��A�ԉ摜�Ƃ��ĉ摜����ق��擾����֐�
	const VecInt& GetCombinedID(const ANIMATION& anim,const WEAPON& weapon);
	// ��Ұ��ݖ��擾�֐�
	const AnimationString& GetAnimString(void)
	{
		return animString;
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
	AnimationString animString;
	// ��Ұ��ݖ��̉摜�̖��O
	std::array<std::vector<std::string>,ANIM_MAX> animationImageName[WEAPON_MAX];
	// �摜����ق𕶎���Ŏ��ʂ��邽�߂̺���
	std::map<std::string, VecInt> imageHandleMap;
	// ��ڲ԰�̱�Ұ��ݖ��̉摜����ق��Ұ��݂Ŏ��ʂ��邽�߂̺���
	std::map<ANIMATION, VecInt> playerHandleMap[WEAPON_MAX];
};

