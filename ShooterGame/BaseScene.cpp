#include "BaseScene.h"

int BaseScene::loadSize_ = 0;

BaseScene::BaseScene(SceneController& sCon):
	sceneCtl_(sCon)
{

}

BaseScene::~BaseScene()
{
}

void BaseScene::SetLoadSize(int size)
{
	loadSize_ = size;
}
