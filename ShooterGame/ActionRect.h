#pragma once
#include "Geometory.h"
#include <string>
// ﾌｧｲﾙから読み込んだ矩形ﾃﾞｰﾀを格納して実際の当たり判定等で使用する矩形情報を入れ込むｸﾗｽ

// 矩形のﾀｲﾌﾟ
// 攻撃矩形なのかくらい矩形なのか
enum class RectType
{
	Attack,
	Damage,
	Max
};

static RectType begin(RectType)
{
	return RectType::Attack;
}
static RectType end(RectType)
{
	return RectType::Max;
}
static RectType operator++(RectType& type)
{
	return (type = (RectType)(std::underlying_type<RectType>::type(type) + 1));
}
static RectType operator*(RectType& type)
{
	return type;
}

struct RectData
{
	int frame_;
	Vector2I begin_;
	Vector2I end_;
	Vector2I size_;
	RectType type_;
	std::string actionName_;

	RectData() :begin_({ 0,0 }), end_({ 0,0 }),
		size_({ 0,0 }), type_(RectType::Max), frame_(0), actionName_("") {};

	RectData(Vector2I begin, Vector2I end, Vector2I size, RectType type, int frame, std::string actionName) :
		begin_(begin), end_(end), size_(size), type_(type), frame_(frame), actionName_(actionName) {};
};

class ActionRect
{
public:
	ActionRect();
	~ActionRect();

	// 矩形ﾃﾞｰﾀの取得
	RectData& GetData(void)
	{
		return data_;
	}

	const Vector2I& GetCenter(void)
	{
		return center_;
	}
	// 描画
	void Draw(const Vector2I& player);

private:
	// 矩形のﾎﾟｼﾞｼｮﾝやｻｲｽﾞの情報
	RectData data_;
	// 矩形の中心ﾎﾟｼﾞｼｮﾝ
	Vector2I center_;
	// 矩形の色
	unsigned int boxcol_;
};



