#include <vector>
#include <map>
#include <string>
#include <array>

#include "ActorType.h"
#include "ObjectType.h"
#include "Geometory.h"
#include "WeaponType.h"
#include "BulletType.h"

#define lpImage ImageManager::GetInstance()

using VecInt = std::vector<int>;

using ActionSet = std::map<std::string, std::pair<std::pair<int, int>, bool>>;

struct Resource
{
	// ©•ª‚ÌactorType‚Ì–¼‘O
	std::string typeName;
	ActionSet actionNameSet;

	// ÌÚ°Ñ”
	int frame = 0;
	// ±ÆÒ°¼®İ‚ğ•¶š—ñ‚Å”»•Ê
	std::map<std::string, VecInt> imageHandle;
	// ‰æ‘œ•ªŠ„”
	Vector2I divCount_;
	// ‰æ‘œ•ªŠ„»²½Ş
	Vector2I divSize_;
};

struct WeaponResource
{
	std::string weaponName;
	std::map<std::string,VecInt> imageHandle_;
	ActionSet actionNameSet_;

	// ‰æ‘œ•ªŠ„”
	Vector2I divCount_;
	// ‰æ‘œ•ªŠ„»²½Ş
	Vector2I divSize_;
};

struct BulletResource
{
	std::string bulletName;
	std::map<std::string, VecInt> imageHandle_;
	ActionSet actionNameSet_;

	// ‰æ‘œ•ªŠ„”
	Vector2I divCount_;
	// ‰æ‘œ•ªŠ„»²½Ş
	Vector2I divSize_;
};

struct StageResource
{
	// ©•ª‚ÌµÌŞ¼Şª¸ÄÀ²Ìß‚Ì–¼‘O
	std::string typeName;
	// ‰æ‘œÊİÄŞÙ
	int imageHandle = -1;

	Vector2I divSize;
	Vector2I divCount;
};

class ImageManager
{
public:

	static ImageManager& GetInstance(void)
	{
		static ImageManager s_instance;
		return s_instance;
	}
	// ±¸À°‚ÌÛ°ÄŞ
	bool Load(const ActorType& actor,
		std::string filepath, Vector2I divSize, Vector2I divCount);
	// ‰æ‘œ‚Ì•ªŠ„Û°ÄŞ
	bool LoadDiv(std::string name, Vector2I divSize, Vector2I divCount);
	// •ªŠ„“Ç‚İ‚İ‚ğ‚µ‚½‰æ‘œÊİÄŞÙ‚Ìæ“¾
	const VecInt& GetDivID(std::string name);

	// ‰æ‘œ‚ÌÛ°ÄŞ
	void Load(std::string fileName);
	// ½Ã°¼ŞµÌŞ¼Şª¸Ä‚ÌÛ°ÄŞ
	bool LoadStage(const ObjectType& objType, std::string objName);
	bool LoadWeapon(const WeaponType& weaponType, std::string weaponName);
	bool LoadBullet(const BulletType& bulletType,std::string bulletName);
	const VecInt& GetID(const ActorType& actor, std::string filepath);
	const int& GetID(std::string fileName);

	// ½Ã°¼ŞµÌŞ¼Şª¸ÄID‚Ìæ“¾
	const StageResource& GetStageResource(const ObjectType& objType)
	{
		return stageResources_[static_cast<int>(objType)];
	}
	// Ø¿°½‚Ìæ“¾
	const Resource& GetResource(const ActorType& actor)
	{
		return resources_[static_cast<int>(actor)];
	}
	// Ø¿°½‚Ìæ“¾
	const WeaponResource& GetWeaponResource(const WeaponType& weapon)
	{
		return weaponResources_[static_cast<int>(weapon)];
	}

	const BulletResource& GetBulletResource(const BulletType& bullet)
	{
		return bulletResources_[static_cast<int>(bullet)];
	}

	const ActionSet& GetActionSet(ActorType actor)
	{
		return resources_[static_cast<int>(actor)].actionNameSet;
	}
	const std::string& GetActorName(const ActorType& actor)
	{
		return resources_[static_cast<int>(actor)].typeName;
	}
private:
	ImageManager() = default;
	ImageManager(const ImageManager&) = delete;
	void operator=(const ImageManager&) = delete;

	// “oêl•¨“™‚ÌØ¿°½î•ñ
	std::array<Resource, static_cast<int>(ActorType::Max)> resources_;
	std::array<WeaponResource, static_cast<int>(WeaponType::Max)> weaponResources_;

	std::array<BulletResource, static_cast<int>(BulletType::Max)> bulletResources_;

	// ½Ã°¼ŞµÌŞ¼Şª¸Ä‚ÌØ¿°½î•ñ
	std::array<StageResource,static_cast<int>(ObjectType::Max)> stageResources_;

	// ‰æ‘œÊİÄŞÙ(1–‡ŠG)
	std::map<std::string, int> handles_;
	// ‰æ‘œÊİÄŞÙ(•ªŠ„‰æ‘œ)
	std::map<std::string, VecInt> divHandles_;
	void SetUp(ActorType actor);
	// “Ç‚İ‚ñ‚¾‰æ‘œ‚ğ•ªŠ„‚µ‚Ä“Ç‚İ‚İ
	void LoadDerivationGraph(ActorType actor, int handle, Vector2I divSize, Vector2I divCount);
};

