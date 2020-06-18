#include "EffectManager.h"



EffectManager::EffectManager()
{
	effectNum = 0;
}


EffectManager::~EffectManager()
{
}

void EffectManager::SetPos(const Vector2 & hitPos)
{
	pos.emplace_back();
	pos[effectNum] = hitPos;
	effectNum++;
}

void EffectManager::UpdateEffect(Vector2 hitPos)
{
	
}

void EffectManager::Draw(void)
{
	
}
