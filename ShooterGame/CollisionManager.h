#pragma once
#include <vector>
#include <string>
#include <map>
#include <memory>

#include "ActionRect.h"


// 矩形情報をﾛｰﾄﾞする為のｼﾝｸﾞﾙﾄﾝｸﾗｽ
using ActRect = std::vector<std::shared_ptr<ActionRect>>;
// 1ﾌﾚｰﾑの中身の矩形情報(複数あるのでvectorにしている)
using FRect = std::vector<ActRect>;
// 1ｱﾆﾒｰｼｮﾝの中身の矩形情報(pair(ｱﾆﾒｰｼｮﾝ文字列とその現在ﾌﾚｰﾑ)で判別可能にする)
using AnimationRect = std::map<std::string, FRect>;
// ﾌﾟﾚｲﾔｰの矩形なのか敵の矩形なのかの識別
using ActorRect = std::map<std::string, AnimationRect>;

class CollisionManager
{
public:
	static CollisionManager& GetInstance(void)
	{
		static CollisionManager s_instance;
		return s_instance;
	}

	void Load(AnimationRect& actorRect, const std::string& actorname);


private:
	CollisionManager() = default;
	CollisionManager(const CollisionManager&) = delete;
	void operator=(const CollisionManager&) = delete;

	// ﾍｯﾀﾞｰﾌｧｲﾙﾎﾟｲﾝﾀ
	FILE* headerFile_;
	// 矩形ﾃﾞｰﾀが入っているﾌｧｲﾙﾎﾟｲﾝﾀ
	FILE* file_;

};

