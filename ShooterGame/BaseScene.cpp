#include "BaseScene.h"

int BaseScene::loadSize_ = 0;

BaseScene::BaseScene(SceneController& sCon):
	sceneCtl_(sCon)
{
	fade_ = Fade::In;
}

BaseScene::~BaseScene()
{
}

void BaseScene::SetLoadSize(int size)
{
	loadSize_ = size;
}
