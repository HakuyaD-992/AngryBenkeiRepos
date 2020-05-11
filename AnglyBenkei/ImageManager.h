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

// 整数型ｺﾝﾃﾅ（画像ﾊﾝﾄﾞﾙを保存する用）
using VecInt = std::vector<int>;
// ｱﾆﾒｰｼｮﾝ毎の文字列用ｺﾝﾃﾅ(ｱﾆﾒｰｼｮﾝの名前を保存する用)
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
	// ｱﾆﾒｰｼｮﾝ毎のｲﾒｰｼﾞﾈｰﾑｾｯﾄ
	void SetAnimationName(const ANIMATION& anim,const WEAPON& weapon,FileName fileName);
	// ｱﾆﾒｰｼｮﾝ毎の文字列をｾｯﾄ
	void SetAnimationString(const Actor& actor,const ANIMATION& anim);
	// 1枚ｻｲｽﾞの画像ﾊﾝﾄﾞﾙ取得関数
	const VecInt& GetID(std::string imageName);
	// 1枚の画像を分割して画像ﾊﾝﾄﾞﾙを取得する際の関数
	const VecInt& GetID(std::string imageName,Vector2 divSize,Vector2 divCount);
	// 1枚ｻｲｽﾞの画像を連番画像として画像ﾊﾝﾄﾞﾙを取得する関数
	const VecInt& GetCombinedID(const ANIMATION& anim,const WEAPON& weapon);
	// ｱﾆﾒｰｼｮﾝ名取得関数
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

	// 画像の名前
	std::string imageName;
	// ｱﾆﾒｰｼｮﾝ名
	AnimationString animString;
	// ｱﾆﾒｰｼｮﾝ毎の画像の名前
	std::array<std::vector<std::string>,ANIM_MAX> animationImageName[WEAPON_MAX];
	// 画像ﾊﾝﾄﾞﾙを文字列で識別するためのｺﾝﾃﾅ
	std::map<std::string, VecInt> imageHandleMap;
	// ﾌﾟﾚｲﾔｰのｱﾆﾒｰｼｮﾝ毎の画像ﾊﾝﾄﾞﾙをｱﾆﾒｰｼｮﾝで識別するためのｺﾝﾃﾅ
	std::map<ANIMATION, VecInt> playerHandleMap[WEAPON_MAX];
};

