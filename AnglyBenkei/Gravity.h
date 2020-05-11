#pragma once
#include <mutex>
#include "Vector2.h"

// ‚©‚©‚éˆê’èd—Í
#define GRAVITY 0.3f

class Gravity
{
public:
	Gravity(void);
	~Gravity();

	// •¨‘Ì‚É‘Î‚µ‚Äd—Í‚ğ‚©‚¯‚éŠÖ”
	void PutGravityOnActor(Vector2& pos);

private:
	// •¨‘Ì‚É‘Î‚µ‚Ä‚©‚©‚éd—Í
	float gPower;
};

