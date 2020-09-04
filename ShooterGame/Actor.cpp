#include <DxLib.h>
#include "Actor.h"
#include "Floor.h"
#include "ObjectType.h"
#include "ScreenEffectMng.h"
#include "ImageManager.h"

Actor::Actor()
{
	exRate_ = 1.0f;
	rotRate_ = 0.0f;

	animationCount_ = 0.0f;
	count_ = 0.0f;
	isTurnLeft_ = false;
	isMove_ = false;
	speed_ = { 0,0 };
	zSpeed_ = 0;
	jumpSpeed_ = 0;
	jumpFirstSpeed_ = -13.0f;
	jumpForce_ = 0.0f;
	isJump_ = false;
	isAnimEnd_ = false;
	isAttack_ = false;

	// �܂��ҋ@��Ԃɏ�����
	//currentAnimation_ = "idle";

	gravity_ = new Gravity();

}

Actor::~Actor()
{
}

bool Actor::OnFloor(void)
{
	if (pos_.y >= 500)
	{
		return true;
	}
	return false;
}

bool Actor::InFloor(void)
{
	if (pos_.x - 1	>= GetPos().x && pos_.y + 63 >= GetPos().y &&
		pos_.x + 65 <= 800		  && pos_.y + 65 <= GetPos().y + 166)
	{
		return true;
	}
	return false;
}


bool Actor::Initialize(void)
{
	// ImageLoader�׽�̎g�p
	auto& imageMng = ImageManager::GetInstance();
	auto imageResource = imageMng.GetResource(type_);

	// ��Ұ����ڰсA��Ұ��ݖ��݂̒�グ
	auto animSet = imageMng.GetActionSet(type_);

	// ���ߕʂɌX�̱�Ұ��ݖ��Ʊ�Ұ����ڰт̊i�[
	// �����������炱��͂���Ȃ�...??
	for (auto anim = animSet.begin(); anim != animSet.end(); anim++)
	{
		animationSet_.try_emplace(anim->first, anim->second.first.second - anim->second.first.first);
		isLoop_.try_emplace(anim->first, anim->second.second);
	}

	// ��`���̏�����
	RectInitializer();

	return true;
}

void Actor::RectInitializer(void)
{
	auto& imageMng = ImageManager::GetInstance();
	for (auto animSet = imageMng.GetActionSet(type_).begin();
		animSet != imageMng.GetActionSet(type_).end(); animSet++)
	{
		rect_.try_emplace(animSet->first);
		rect_[animSet->first].resize((animSet->second.first.second - animSet->second.first.first) + 1);
	}

	auto name = imageMng.GetActorName(type_);
	auto& collisionMng = CollisionManager::GetInstance();

	collisionMng.Load(rect_, name);
}

void Actor::Draw(void)
{
	auto& imageMng = ImageManager::GetInstance();

	drawPos_ = Vector2I(pos_.x, pos_.y + (z_ / 2));
	if (type_ == ActorType::Player)
	{
		lpS_Effect.DrawRotaGraph(Vector2I(drawPos_.x, drawPos_.y),
			exRate_, rotRate_,
			imageMng.GetID(type_, currentAnimation_)[animationCount_],
			true, isTurnLeft_);
	}
	else
	{
		lpS_Effect.DrawRotaGraph(Vector2I(drawPos_.x , drawPos_.y) + lpS_Effect.MoveAmountCalculator(ObjectType::Floor),
			exRate_, rotRate_,
			imageMng.GetID(type_, currentAnimation_)[animationCount_],
			true, isTurnLeft_);
	}

	DrawFormatString(100, 100, 0xffffff, "pos.x:%d,pos.y:%d,pos.z:%d", pos_.x, pos_.y, z_);
	DrawFormatString(100, 150, 0xffffff, "animationCount:%f",animationCount_);

	// ���̱�Ұ��݂ł̋�`���������Ċi�[
	auto it = rect_.find(currentAnimation_);
	// ���̱�Ұ��݂̌��݂��ڰт̒��̋�`����S�������ĕ`��
	for (auto collider : it->second[animationCount_])
	{
		collider->Draw(drawPos_);
	}
}

void Actor::UpDateAnimation(const std::string& animName)
{
	animationCount_ += 0.1f;
	if (animationSet_.find(animName) != animationSet_.end())
	{
		if ((int)animationCount_ >= animationSet_.find(animName)->second)
		{
			if (isLoop_[animName])
			{
				animationCount_ = 0.0f;
			}
			else
			{
				animationCount_ = animationSet_.find(animName)->second;
				isAttack_ = false;
				isAnimEnd_ = true;
			}
		}
	}
}

void Actor::ChangeAnimation(std::string animName)
{
	if (currentAnimation_ == animName)
	{
		return;
	}
	if (animationSet_.find(animName) != animationSet_.end())
	{
		currentAnimation_ = animName;
		animationCount_ = 0;
		isAnimEnd_ = false;
	}
	else
	{
		animationCount_ = 0;
		isAnimEnd_ = true;
	}

}
