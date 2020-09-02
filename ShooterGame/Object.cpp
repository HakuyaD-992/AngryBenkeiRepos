#include <DxLib.h>
#include "Object.h"
#include "ImageManager.h"

Object::Object()
{
	exRate_ = 1.0;
	rotRate_ = 0.0;
}

Object::~Object()
{
}

void Object::Draw(void)
{
	DrawRotaGraph(pos_.x, pos_.y, exRate_, rotRate_, imageHandle_, true, false);
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
	imageHandle_ = imageMng.GetStageID(type_).imageHandle;

	return true;
}
