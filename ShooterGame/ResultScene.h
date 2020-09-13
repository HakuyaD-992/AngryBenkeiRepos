#pragma once
#include "BaseScene.h"
class ResultScene :
	public BaseScene
{
public:
	ResultScene(SceneController& sCon, int useBullet, bool winFlag);
	~ResultScene();

	void UpDate(const std::vector<std::shared_ptr<Input>>& input);
	void Initialize(void);
	void Draw(void);

private:
	int useBullet;
	//@
	bool winFlag;
};

