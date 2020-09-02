#include "Enemy.h"
#include "ImageManager.h"

Enemy::Enemy(std::list<std::shared_ptr<ControlledPlayer>>& player):
	player_(player)
{

}

Enemy::~Enemy()
{
}

bool Enemy::Initialize(void)
{
	auto& imageMng = ImageManager::GetInstance();
	auto imageResource = imageMng.GetResource(type_);

	// �e���߂̉摜�ް���۰��
	imageMng.Load(type_, "atlus", imageResource.divSize_, imageResource.divCount_);
	return true;
}

void Enemy::SetPos(const Vector2I& pos,int z)
{
	pos_ = pos;
	z_ = z;
}
