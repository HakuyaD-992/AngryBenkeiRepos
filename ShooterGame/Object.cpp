#include <DxLib.h>
#include "Object.h"
#include "ScreenEffectMng.h"
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
	lpS_Effect.DrawRotaGraph(Vector2I(pos_.x, pos_.y), exRate_, rotRate_, imageHandle_, true, false);
}

void Object::SetPos(const Vector2I& pos)
{
	pos_ = pos;
}

bool Object::Initialize(void)
{
	auto& imageMng = ImageManager::GetInstance();

	imageMng.LoadStage(type_, name_);

	// å¬ÅXÇÃµÃﬁºﬁ™∏ƒ
	imageHandle_ = imageMng.GetStageID(type_).imageHandle;

	return true;
}
