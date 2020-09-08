#pragma once
#include <map>
#include "Geometory.h"
#include "Enemy.h"

using namespace std;
class Exoskeleton :
	public Enemy
{
public:
	Exoskeleton(Vector2I pos,int z,ActorType type,
		std::vector<std::shared_ptr<ControlledPlayer>>& player);
	~Exoskeleton();

	void UpDate(void);
	void Draw_(void);

	void (Exoskeleton::* updater)(void);

private:
	// ‘–‚é
	void Run(void);
	// ÌßÚ²Ô°‚ÌZ²‚É©•ª‚ÌZ²‚ğ‡‚í‚¹‚é
	void ArrangementZ(void);
	// Z²‚ªÌßÚ²Ô°‚Æ‚ ‚Á‚½‚çUŒ‚‚ğ‚·‚é(’e‚ğo‚·)
	void Attack(void);
	// ’e‚ª–³‚­‚È‚ê‚Îˆê’U‘Ş”ğ
	void Evacuation(void);
	// ’e‚Ì•â[
	void RefillBullet(void);

	int frame;

	vector<pair<Vector2F, int>> afterimage_limit;
};

