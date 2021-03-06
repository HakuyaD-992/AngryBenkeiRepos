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
	// 自分のactorTypeの名前
	std::string typeName;
	ActionSet actionNameSet;

	// ﾌﾚｰﾑ数
	int frame = 0;
	// ｱﾆﾒｰｼｮﾝを文字列で判別
	std::map<std::string, VecInt> imageHandle;
	// 画像分割数
	Vector2I divCount_;
	// 画像分割ｻｲｽﾞ
	Vector2I divSize_;
};

struct WeaponResource
{
	std::string weaponName;
	std::map<std::string,VecInt> imageHandle_;
	ActionSet actionNameSet_;

	// 画像分割数
	Vector2I divCount_;
	// 画像分割ｻｲｽﾞ
	Vector2I divSize_;
};

struct BulletResource
{
	std::string bulletName;
	std::map<std::string, VecInt> imageHandle_;
	ActionSet actionNameSet_;

	// 画像分割数
	Vector2I divCount_;
	// 画像分割ｻｲｽﾞ
	Vector2I divSize_;
};

struct StageResource
{
	// 自分のｵﾌﾞｼﾞｪｸﾄﾀｲﾌﾟの名前
	std::string typeName;
	// 画像ﾊﾝﾄﾞﾙ
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
	// ｱｸﾀｰのﾛｰﾄﾞ
	bool Load(const ActorType& actor,
		std::string filepath, Vector2I divSize, Vector2I divCount);
	// 画像の分割ﾛｰﾄﾞ
	bool LoadDiv(std::string name, Vector2I divSize, Vector2I divCount);
	// 分割読み込みをした画像ﾊﾝﾄﾞﾙの取得
	const VecInt& GetDivID(std::string name);

	// 画像のﾛｰﾄﾞ
	void Load(std::string fileName);
	// ｽﾃｰｼﾞｵﾌﾞｼﾞｪｸﾄのﾛｰﾄﾞ
	bool LoadStage(const ObjectType& objType, std::string objName);
	bool LoadWeapon(const WeaponType& weaponType, std::string weaponName);
	bool LoadBullet(const BulletType& bulletType,std::string bulletName);
	const VecInt& GetID(const ActorType& actor, std::string filepath);
	const int& GetID(std::string fileName);

	// ｽﾃｰｼﾞｵﾌﾞｼﾞｪｸﾄIDの取得
	const StageResource& GetStageResource(const ObjectType& objType)
	{
		return stageResources_[static_cast<int>(objType)];
	}
	// ﾘｿｰｽの取得
	const Resource& GetResource(const ActorType& actor)
	{
		return resources_[static_cast<int>(actor)];
	}
	// ﾘｿｰｽの取得
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

	// 登場人物等のﾘｿｰｽ情報
	std::array<Resource, static_cast<int>(ActorType::Max)> resources_;
	std::array<WeaponResource, static_cast<int>(WeaponType::Max)> weaponResources_;

	std::array<BulletResource, static_cast<int>(BulletType::Max)> bulletResources_;

	// ｽﾃｰｼﾞｵﾌﾞｼﾞｪｸﾄのﾘｿｰｽ情報
	std::array<StageResource,static_cast<int>(ObjectType::Max)> stageResources_;

	// 画像ﾊﾝﾄﾞﾙ(1枚絵)
	std::map<std::string, int> handles_;
	// 画像ﾊﾝﾄﾞﾙ(分割画像)
	std::map<std::string, VecInt> divHandles_;
	void SetUp(ActorType actor);
	// 読み込んだ画像を分割して読み込み
	void LoadDerivationGraph(ActorType actor, int handle, Vector2I divSize, Vector2I divCount);
};

