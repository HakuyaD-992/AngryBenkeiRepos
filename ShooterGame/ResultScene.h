#pragma once
#include <map>
#include <functional>
#include <array>
#include "BaseScene.h"
#include "Geometory.h"

enum class StringType
{
	Time,
	HitRate,
	Score,
	PushB,
	Max
};

class ResultScene :
	public BaseScene
{
public:
	ResultScene(SceneController& sCon, int useBullet,time_t& frame,int& defeatEnemy);
	~ResultScene();

	void UpDate(const std::vector<std::shared_ptr<Input>>& input);
	void Initialize(void);
	void Draw(void);

private:
	float useBullet;
	int clearTime_;

	int clearTime_t;
	int clearTime_secf1;
	int clearTime_secf2;

	int stringSpeed_;

	void(ResultScene::* updater_)(void);

	StringType strType_;

	bool drawPercentFlag_;

	float totalDefeatEnemyNum_;
	float hitRate_;

	void FirstUpdate(void);
	void SecondUpdate(void);
	void ThirdUpdate(void);
	void FinalUpdate(void);

	Vector2I percentPos_;
	std::array<Vector2I, static_cast<int>(StringType::Max)> stringPos_;

	std::array<float, static_cast<int>(StringType::Max)> fadeCnt_;

	float volPan_;

	float lineAlphaval_[3];

	int box_end[3];

	bool playSeFlag_[3];

	int totalScore_;
};

