#pragma once
#include "BaseScene.h"
#include "Geometory.h"

class GameOver :
	public BaseScene
{
public:
	GameOver(SceneController& sCon);
	~GameOver();
private:
	void UpDate(const std::vector<std::shared_ptr<Input>>& input);
	void Draw(void);
	void Initialize(void);

	int fadeCnt_;
	Vector2I logoPos_;
	int logoShakeRate_;
	int logoFlickCnt_;

	int shakeFrame_;

	int fadeCnt_backtotitle;
	// ƒ^ƒCƒgƒ‹‚É–ß‚éÛ‚É•¶š‚ğŒõ‚ç‚¹‚é¶³İÄ
	float pushAddval_;

	bool returnTitleFlag_;
	bool brightFlag_;

	float exRate_;

	bool littleExtendFlag_;
};

