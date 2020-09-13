#include <DxLib.h>
#include "Object.h"
#include "ControlledPlayer.h"
#include "ScreenEffectMng.h"
#include "ImageManager.h"

<<<<<<< HEAD
Object::Object(std::shared_ptr<ControlledPlayer>& player):
=======
Object::Object(std::vector<std::shared_ptr<ControlledPlayer>>& player):
>>>>>>> 56ac109e597b0e82e8d13a0ad1b670f3c322930f
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
