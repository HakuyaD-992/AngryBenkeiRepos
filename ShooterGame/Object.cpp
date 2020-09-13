#include <DxLib.h>
#include "Object.h"
#include "ScreenEffectMng.h"
#include "ImageManager.h"

Object::Object(std::shared_ptr<ControlledPlayer>& player):
	player_(player)
{
	exRate_ = 1.0;
	rotRate_ = 0.0;
}

Object::~Object()
{
}

void Object::SetPos(const Vector2I& pos)
{
	pos_ = pos;
}

bool Object::Initialize(void)
{
	auto& imageMng = ImageManager::GetInstance();

	imageMng.LoadStage(type_, name_);

	// ŒÂX‚ÌµÌŞ¼Şª¸Ä
	imageHandle_ = imageMng.GetStageResource(type_).imageHandle;

	return true;
}
