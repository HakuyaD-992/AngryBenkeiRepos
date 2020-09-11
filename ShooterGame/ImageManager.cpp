#include <DxLib.h>
#include "ImageManager.h"

bool ImageManager::Load(const ActorType& actor, std::string filepath, Vector2I divSize, Vector2I divCount)
{
	if (resources_[static_cast<int>(actor)].imageHandle.find(filepath) ==
		resources_[static_cast<int>(actor)].imageHandle.end())
	{
		SetUp(actor);

		int handle = -1;
		switch (actor)
		{
		case ActorType::Player:
			resources_[static_cast<int>(actor)].typeName = "Player";
			resources_[static_cast<int>(actor)].divSize_ = Vector2I(64, 64);
			resources_[static_cast<int>(actor)].divCount_ = Vector2I(8, 4);
			break;

		case ActorType::Pod:
			resources_[static_cast<int>(actor)].typeName = "Pod";
			resources_[static_cast<int>(actor)].divSize_ = Vector2I(55, 55);
			resources_[static_cast<int>(actor)].divCount_ = Vector2I(5, 6);
			break;
		case ActorType::Exoskeleton:
			resources_[static_cast<int>(actor)].typeName = "Exoskeleton";
			resources_[static_cast<int>(actor)].divSize_ = Vector2I(48, 48);
			resources_[static_cast<int>(actor)].divCount_ = Vector2I(8, 2);

			break;
		case ActorType::Spacenaut:
			resources_[static_cast<int>(actor)].typeName = "Spacenaut";
			resources_[static_cast<int>(actor)].divSize_ = Vector2I(68, 68);
			resources_[static_cast<int>(actor)].divCount_ = Vector2I(10, 2);

			break;

		case ActorType::Bigboy:
			resources_[static_cast<int>(actor)].typeName = "Bigboy";
			resources_[static_cast<int>(actor)].divSize_ = Vector2I(300, 300);
			resources_[static_cast<int>(actor)].divCount_ = Vector2I(6, 7);
			break;
		case ActorType::Max:
		default:
			return false;
			break;
		}

		auto pathName = "Images/" + resources_[static_cast<int>(actor)].typeName +
			"_" + filepath + ".png";
		for (auto action : resources_[static_cast<int>(actor)].actionNameSet)
		{
			if (resources_[static_cast<int>(actor)].imageHandle.find(action.first) ==
				resources_[static_cast<int>(actor)].imageHandle.end())
			{
				resources_[static_cast<int>(actor)].imageHandle[action.first].resize((action.second.first.second - action.second.first.first) + 1);
			}
		}
		handle = LoadGraph(pathName.c_str());
		if (handle == -1)
		{
			return false;
		}

		// DerivationGraph()Ç≈éwíËç¿ïWï™äÑÇµÇƒ∏ﬁ◊Ã®Ø∏ ›ƒﬁŸéÊìæ
		LoadDerivationGraph(actor, handle, divSize, divCount);
	}
	return true;
}

bool ImageManager::LoadDiv(std::string name, Vector2I divSize, Vector2I divCount)
{
	if (divHandles_.find(name) == divHandles_.end())
	{
		auto filepath = "Images/" + name + ".png";
		divHandles_[name].resize(divCount.x * divCount.y);

		LoadDivGraph(filepath.c_str(), divCount.x * divCount.y,
			divCount.x, divCount.y, divSize.x, divSize.y, &divHandles_[name][0]);
	}
	return true;
}

const VecInt& ImageManager::GetDivID(std::string name)
{
	return divHandles_[name];
}

bool ImageManager::LoadStage(const ObjectType& objType, std::string objName)
{
	std::string filename = "";
	stageResources_[static_cast<int>(objType)].divSize = Vector2I(800, 420);
	stageResources_[static_cast<int>(objType)].divCount = Vector2I(1, 1);
	filename = "Images/Objects/" + objName + ".png";

	stageResources_[static_cast<int>(objType)].imageHandle
		= LoadGraph(filename.c_str());
	return true;
}

bool ImageManager::LoadWeapon(const WeaponType& weaponType, std::string weaponName)
{
	switch (weaponType)
	{
	case WeaponType::Pistol:
		weaponResources_[static_cast<int>(weaponType)].actionNameSet_.try_emplace("non", std::make_pair(std::make_pair(0, 0), false));
		weaponResources_[static_cast<int>(weaponType)].actionNameSet_.try_emplace("fire", std::make_pair(std::make_pair(0, 6), false));
		weaponResources_[static_cast<int>(weaponType)].actionNameSet_.try_emplace("reload", std::make_pair(std::make_pair(0, 0), false));
		weaponResources_[static_cast<int>(weaponType)].divCount_ = Vector2I(3, 3);
		weaponResources_[static_cast<int>(weaponType)].divSize_ = Vector2I(40, 19);
		break;

	case WeaponType::ShotGun:
		weaponResources_[static_cast<int>(weaponType)].actionNameSet_.try_emplace("fire", std::make_pair(std::make_pair(0, 6), false));
		weaponResources_[static_cast<int>(weaponType)].actionNameSet_.try_emplace("non", std::make_pair(std::make_pair(7, 7), false));
		weaponResources_[static_cast<int>(weaponType)].actionNameSet_.try_emplace("reload", std::make_pair(std::make_pair(7, 15), false));
		weaponResources_[static_cast<int>(weaponType)].divCount_ = Vector2I(4, 4);
		weaponResources_[static_cast<int>(weaponType)].divSize_ = Vector2I(90, 21);

		break;
	case WeaponType::SubMachineGun:
		weaponResources_[static_cast<int>(weaponType)].actionNameSet_.try_emplace("fire", std::make_pair(std::make_pair(0, 6), false));
		weaponResources_[static_cast<int>(weaponType)].actionNameSet_.try_emplace("non", std::make_pair(std::make_pair(0, 0), false));
		weaponResources_[static_cast<int>(weaponType)].actionNameSet_.try_emplace("reload", std::make_pair(std::make_pair(7, 8), false));
		weaponResources_[static_cast<int>(weaponType)].divCount_ = Vector2I(4, 3);
		weaponResources_[static_cast<int>(weaponType)].divSize_ = Vector2I(80, 20);
		break;
	case WeaponType::Max:
		break;
	default:
		break;
	}
	auto filepath = "Images/Weapons/" + weaponName + ".png";

	auto handle = LoadGraph(filepath.c_str());

	for (auto resource : weaponResources_[static_cast<int>(weaponType)].actionNameSet_)
	{
		weaponResources_[static_cast<int>(weaponType)].imageHandle_[resource.first].resize
		(resource.second.first.second - resource.second.first.first + 1);
		int count = 0;
		while (count <= resource.second.first.second- resource.second.first.first)
		{
			int spriteCount = count + resource.second.first.first;
			weaponResources_[static_cast<int>(weaponType)].imageHandle_[resource.first][count]
				= DerivationGraph((spriteCount % weaponResources_[static_cast<int>(weaponType)].divCount_.x) * weaponResources_[static_cast<int>(weaponType)].divSize_.x,
					(spriteCount / weaponResources_[static_cast<int>(weaponType)].divCount_.x) * weaponResources_[static_cast<int>(weaponType)].divSize_.y,
					weaponResources_[static_cast<int>(weaponType)].divSize_.x, weaponResources_[static_cast<int>(weaponType)].divSize_.y, handle);
			count++;
		}
	}
	return true;
}

bool ImageManager::LoadBullet(const BulletType& bulletType, std::string bulletName)
{
	switch (bulletType)
	{
	case BulletType::PistolBullet:
		bulletResources_[static_cast<int>(bulletType)].actionNameSet_.try_emplace("non", std::make_pair(0, 0), false);
		bulletResources_[static_cast<int>(bulletType)].divCount_ = Vector2I(1, 1);
		bulletResources_[static_cast<int>(bulletType)].divSize_ = Vector2I(5, 2);

		break;
	case BulletType::ShotBullet:
		bulletResources_[static_cast<int>(bulletType)].actionNameSet_.try_emplace("non", std::make_pair(1, 1),false);
		bulletResources_[static_cast<int>(bulletType)].actionNameSet_.try_emplace("landed", std::make_pair(2, 7), false);
		bulletResources_[static_cast<int>(bulletType)].actionNameSet_.try_emplace("hit_something", std::make_pair(8, 15), false);
		bulletResources_[static_cast<int>(bulletType)].divCount_ = Vector2I(8, 2);
		bulletResources_[static_cast<int>(bulletType)].divSize_ = Vector2I(16, 16);
		break;
	case BulletType::MachineBullet:
		bulletResources_[static_cast<int>(bulletType)].actionNameSet_.try_emplace("non", std::make_pair(0, 0), false);
		bulletResources_[static_cast<int>(bulletType)].divCount_ = Vector2I(1, 1);
		bulletResources_[static_cast<int>(bulletType)].divSize_ = Vector2I(8, 3);
		break;

	case BulletType::PodBullet:
		bulletResources_[static_cast<int>(bulletType)].actionNameSet_.try_emplace("non", std::make_pair(0, 0), false);
		bulletResources_[static_cast<int>(bulletType)].divCount_ = Vector2I(1, 1);
		bulletResources_[static_cast<int>(bulletType)].divSize_ = Vector2I(8, 8);
	case BulletType::SpacenautBullet:
		bulletResources_[static_cast<int>(bulletType)].actionNameSet_.try_emplace("non", std::make_pair(0, 0), false);
		bulletResources_[static_cast<int>(bulletType)].divCount_ = Vector2I(1, 1);
		bulletResources_[static_cast<int>(bulletType)].divSize_ = Vector2I(8, 4);
		break;

		

	default:
		break;
	}
	auto filepath = "Images/Bullets/" + bulletName + ".png";
	auto handle = LoadGraph(filepath.c_str());

	for (auto resource : bulletResources_[static_cast<int>(bulletType)].actionNameSet_)
	{
		bulletResources_[static_cast<int>(bulletType)].imageHandle_[resource.first].resize
		(resource.second.first.second - resource.second.first.first + 1);
		int count = 0;
		while (count <= resource.second.first.second - resource.second.first.first)
		{
			int spriteCount = count + resource.second.first.first;
			bulletResources_[static_cast<int>(bulletType)].imageHandle_[resource.first][count]
				= DerivationGraph((spriteCount % bulletResources_[static_cast<int>(bulletType)].divCount_.x)* bulletResources_[static_cast<int>(bulletType)].divSize_.x,
				(spriteCount / bulletResources_[static_cast<int>(bulletType)].divCount_.x)* bulletResources_[static_cast<int>(bulletType)].divSize_.y,
					bulletResources_[static_cast<int>(bulletType)].divSize_.x, bulletResources_[static_cast<int>(bulletType)].divSize_.y, handle);
			count++;
		}
	}
	return true;
}

const VecInt& ImageManager::GetID(const ActorType& actor, std::string animName)
{
	return resources_[static_cast<int>(actor)].imageHandle[animName];
}

const int& ImageManager::GetID(std::string fileName)
{
	return handles_[fileName];
}

void ImageManager::Load(std::string fileName)
{
	auto filepath = "Images/" + fileName + ".png";

	handles_.try_emplace(fileName, LoadGraph(filepath.c_str()));
}

void ImageManager::SetUp(ActorType actor)
{
	switch (actor)
	{
	case ActorType::Player:
		resources_[static_cast<int>(actor)].actionNameSet.try_emplace("attack", std::make_pair(std::make_pair(0, 3), false));
		resources_[static_cast<int>(actor)].actionNameSet.try_emplace("idle", std::make_pair(std::make_pair(0, 5), true));
		resources_[static_cast<int>(actor)].actionNameSet.try_emplace("run", std::make_pair(std::make_pair(16, 23), true));
		resources_[static_cast<int>(actor)].actionNameSet.try_emplace("jump", std::make_pair(std::make_pair(24, 24), false));
		resources_[static_cast<int>(actor)].actionNameSet.try_emplace("fall", std::make_pair(std::make_pair(26, 29), false));
		resources_[static_cast<int>(actor)].actionNameSet.try_emplace("hit", std::make_pair(std::make_pair(9, 11), false));

		break;

	case ActorType::Pod:
		resources_[static_cast<int>(actor)].actionNameSet.try_emplace("idle", std::make_pair(std::make_pair(0, 3), true));
		resources_[static_cast<int>(actor)].actionNameSet.try_emplace("attack_prepare", std::make_pair(std::make_pair(6, 13), false));
		resources_[static_cast<int>(actor)].actionNameSet.try_emplace("attack_release", std::make_pair(std::make_pair(15, 19), false));
		resources_[static_cast<int>(actor)].actionNameSet.try_emplace("walk", std::make_pair(std::make_pair(20, 25), true));
		resources_[static_cast<int>(actor)].actionNameSet.try_emplace("hit", std::make_pair(std::make_pair(5, 6), false));
		resources_[static_cast<int>(actor)].actionNameSet.try_emplace("death", std::make_pair(std::make_pair(26, 31), false));

		break;
	case ActorType::Exoskeleton:
		resources_[static_cast<int>(actor)].actionNameSet.try_emplace("run", std::make_pair(std::make_pair(0, 7), true));
		resources_[static_cast<int>(actor)].actionNameSet.try_emplace("death", std::make_pair(std::make_pair(8, 13), false));

		break;
	case ActorType::Spacenaut:
		resources_[static_cast<int>(actor)].actionNameSet.try_emplace("attack", std::make_pair(std::make_pair(1, 1), false));
		resources_[static_cast<int>(actor)].actionNameSet.try_emplace("walk", std::make_pair(std::make_pair(0, 9), true));
		resources_[static_cast<int>(actor)].actionNameSet.try_emplace("death", std::make_pair(std::make_pair(10, 15), false));
		break;
	case ActorType::Bigboy:
		resources_[static_cast<int>(actor)].actionNameSet.try_emplace("idle", std::make_pair(std::make_pair(0, 5), true));
		resources_[static_cast<int>(actor)].actionNameSet.try_emplace("hit", std::make_pair(std::make_pair(6, 11), false));
		resources_[static_cast<int>(actor)].actionNameSet.try_emplace("walk", std::make_pair(std::make_pair(12, 18), true));
		resources_[static_cast<int>(actor)].actionNameSet.try_emplace("attack", std::make_pair(std::make_pair(19, 26), false));
		resources_[static_cast<int>(actor)].actionNameSet.try_emplace("death", std::make_pair(std::make_pair(27, 39), false));

		break;
	case ActorType::Max:
		break;
	default:
		break;
	}
}

void ImageManager::LoadDerivationGraph(ActorType actor, int handle, Vector2I divSize, Vector2I divCount)
{

	for (auto action : resources_[static_cast<int>(actor)].actionNameSet)
	{
		int count = 0;
		while (count <= action.second.first.second - action.second.first.first)
		{
			int spriteCount = count + action.second.first.first;
			resources_[static_cast<int>(actor)].imageHandle[action.first][count]
				= DerivationGraph((spriteCount % resources_[static_cast<int>(actor)].divCount_.x) * resources_[static_cast<int>(actor)].divSize_.x,
					(spriteCount / resources_[static_cast<int>(actor)].divCount_.x) * resources_[static_cast<int>(actor)].divSize_.y,
					resources_[static_cast<int>(actor)].divSize_.x, resources_[static_cast<int>(actor)].divSize_.y, handle);
			count++;
		}
	}
}
