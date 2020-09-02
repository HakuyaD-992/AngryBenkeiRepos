#pragma once
#include <array>
#include <list>
#include <memory>
#include <unordered_map>

#include "BaseScene.h"
//#include "CollisionLoader.h"
#include "ActorType.h"
#include "Fps.h"

class ControlledPlayer;
class Enemy;
//class ShotBase;
//class Spawner;
class Object;
class Spawner;

using ObjectPtr = std::shared_ptr<Object>;
using ObjectList = std::list<ObjectPtr>;

class PlayScene :
	public BaseScene
{
public:
	PlayScene(SceneController& sCon);
	~PlayScene();

private:
	void UpDate(const std::vector<std::shared_ptr<Input>>& input);
	void Draw(void);
	void DrawPlayer(const std::shared_ptr<ControlledPlayer>& player);
	void Initialize(void);
	void AddObject(ObjectPtr object);
	// 2��ڲ԰�ݽ�ݽ����p�׸�
	bool is2PCreate_;
	// ���s�׸�
	bool zFlag_;

	// �e��ڲ԰�A�G�̖��O
	std::array<std::string, static_cast<int>(ActorType::Max)> actorName_;

	std::list<std::shared_ptr<ControlledPlayer>> playerList_;
	std::list<std::shared_ptr<Enemy>> enemyList_;
	//std::list<std::shared_ptr<Spawner>> spawners_;

	ObjectList objList_;
	// �ڰ�ڰ�
	Fps fps_;

	int frame_;
	// ��߰Ű
	std::shared_ptr<Spawner> spawner_;
};



