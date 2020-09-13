#pragma once
#include "BaseScene.h"

class LoadScene :
	public BaseScene
{
public:
	LoadScene(SceneController& sCon);
	~LoadScene();

	void UpDate(const std::vector<std::shared_ptr<Input>>& input);
	void Initialize(void);
	void Draw(void);
private:
	void NowLoading(void);
	void Standby(void);
	void StartNext(void);

	void LoadSoundResources(void);
	void LoadImageResources(void);

	void(LoadScene::* updater_)(void);

	int loadTime_;
	int loadCnt_;
	int standbyCnt_;

	float exRate_;

	bool standbyFlag_;
};

