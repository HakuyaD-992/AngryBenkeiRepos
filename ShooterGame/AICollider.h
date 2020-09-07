#pragma once
#include "Geometory.h"
#include "ActorType.h"

constexpr int size = 100;

// “G‚ÌAIÀŒ»‚Ì‚½‚ß‚Ìº×²ÀŞ°¸×½
// “G“¯m‚ª‚Ô‚Â‚©‚ê‚ÎAI‹N“®
class Enemy;

class AICollider
{
public:
	AICollider();
	~AICollider();
	// Îß¼Ş¼®İ±¯ÌßÃŞ°Ä
	void SetPos(const Vector2I& pos,const int& z);
	// º×²ÀŞ°ÎŞ¯¸½•`‰æ
	void Draw(void);

	// Îß¼Ş¼®İæ“¾ŠÖ”
	const Vector2I& GetPos(void)
	{
		return pos_;
	}
	const int& GetZPos(void)
	{
		return z_;
	}

private:
	Vector2I pos_;
	int z_;

};

