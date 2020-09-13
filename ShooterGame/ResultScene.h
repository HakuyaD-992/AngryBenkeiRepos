#pragma once
#include "BaseScene.h"
class ResultScene :
	public BaseScene
{
public:
	ResultScene(SceneController& sCon);
	~ResultScene();

	void UpDate(const std::vector<std::shared_ptr<Input>>& input);
	void Initialize(void);
	void Draw(void);

private:

};

