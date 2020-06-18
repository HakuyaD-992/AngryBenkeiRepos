#include "Collider.h"

std::once_flag Collider::onceflag;
Collider* Collider::colliderIns = nullptr;

Collider::Collider()
{
}

Collider::~Collider()
{
}

void Collider::Create(void)
{
	if (colliderIns == nullptr)
	{
		colliderIns = new Collider();
	}
}

void Collider::Destroy(void)
{
	if (colliderIns != nullptr)
	{
		delete colliderIns;
	}
	colliderIns = nullptr;
}

void Collider::SetPlayerDataFile(const Actor & actor, const ANIMATION & pAnimation)
{
	// level resize
	if (playerCollider[pAnimation].playerAnimLevelData.size() <= 0)
	{
		playerCollider[pAnimation].playerAnimLevelData.resize(actor.animationLevel[pAnimation]);
	}
	// frame resize
	for (int level = 0; level < actor.animationLevel[pAnimation]; level++)
	{
		if (playerCollider[pAnimation].playerAnimLevelData[level].playerRectData.size() <= 0)
		{
			playerCollider[pAnimation].playerAnimLevelData[level].playerRectData.resize(actor.frameMax[pAnimation][level]);
		}
		for (int frame = 0; frame < actor.frameMax[pAnimation][level]; frame++)
		{
			playerCollider[pAnimation].playerAnimLevelData[level].playerRectData[frame].fileName
				= "CharacterData/" + actor.name + "/" + actor.animationString[pAnimation] + "/" + std::to_string(level + 1)
				+ "/" + actor.animationString[pAnimation] + std::to_string(level + 1) + "_" + std::to_string(frame);
		}
	}
}

void Collider::SetEnemyDataFile(const EnemyStructure & enemy,
								const EnemyAnimation & eAnimation, 
								const ENEMYTYPE & eType)
{
	if (enemyCollider[eType].enemyAnimationRectData[eAnimation].enemyFrameRectData.size() <= 0)
	{
		enemyCollider[eType].enemyAnimationRectData[eAnimation].enemyFrameRectData.resize
		(enemy.enemyFrameMax[eType][eAnimation]);
	}

	for (int frame = 0; frame < enemy.enemyFrameMax[eType][eAnimation]; frame++)
	{
		enemyCollider[eType].enemyAnimationRectData[eAnimation].enemyFrameRectData[frame].fileName
			= "CharacterData/Enemy/" + enemy.enemyTypeName[eType] + "/" + enemy.enemyAnimationString[eAnimation] + "/"
			+ enemy.enemyAnimationString[eAnimation] + "_" + std::to_string(frame);
	}

}
