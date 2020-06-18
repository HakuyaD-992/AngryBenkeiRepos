#pragma once
#include <vector>
#include "Vector2.h"

class EffectManager
{
public:
	EffectManager();
	~EffectManager();

	// set position
	void SetPos(const Vector2& hitPos);
	// update individuals effect
	void UpdateEffect(Vector2 hitPos);
	void Draw(void);

private:
	std::vector<Vector2> pos;
	int effectNum;

};

