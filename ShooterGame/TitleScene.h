#pragma once
#include <array>
#include "BaseScene.h"
#include "Geometory.h"

using ArrayInt = std::array<int, 2>;

// fade in out の際に使用
enum class Fade
{
	In,
	Out,
	Max
};

enum class Next
{
	Manual,
	Game,
	Max
};

class TitleScene :
	public BaseScene
{
public:
	TitleScene(SceneController& sCon);
	~TitleScene();

private:
	void UpDate(const std::vector<std::shared_ptr<Input>>& input);
	void Draw(void);
	void Initialize(void);

	// ﾀｲﾄﾙでの文字列のﾎﾟｼﾞｼｮﾝ
	Vector2I stringPos_;
	// 文字列のｽﾋﾟｰﾄﾞ(fadeIn,outの際に使用)
	Vector2I stringSp_[2];
	// 矢印のﾎﾟｼﾞｼｮﾝ
	Vector2I arrowPos_;

	// ﾌｪｰﾄﾞｲﾝとﾌｪｰﾄﾞｱｳﾄのｶｳﾝﾄ
	int fadeCnt_;
	int pushFadeCnt_;
	// ﾌｪｰﾄﾞｲﾝとｱｳﾄの切り替え
	Fade fade_;
	// 次のｼｰﾝに切り替えるﾌﾗｸﾞ
	Next nextFlag_;
	// 決定ﾎﾞﾀﾝを押したﾌﾗｸﾞ
	bool isNext_;
	// startの文字を広げるｶｳﾝﾄ
	float extendCount_;
	// 上記のｶｳﾝﾄを加算していくﾌﾗｸﾞ
	bool extendFlag_;
	// startの文字をだんだん透過させていくアルファ値
	float alphaCount_;
};

