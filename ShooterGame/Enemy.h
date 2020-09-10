#pragma once
#include <memory>
#include <vector>
#include <functional>
#include "Actor.h"

class ControlledPlayer;
class BulletBase;
class AIBase;
class AICollider;

// “G‚ÌAI½Ã°Ä
enum class AIState
{
	// •à‚­
	Walk,
	// ÌßÚ²Ô°‚Ì”wŒã‚É‘–‚è”²‚¯‚é
	Run,
	// UŒ‚
	Attack,
	// ÌßÚ²Ô°‚ÌZ²‚Æ‡‚í‚¹‚é
	ZArrange,
	Max
};

class Enemy :
	public Actor
{
public:
	Enemy(std::vector<std::shared_ptr<ControlledPlayer>>& player);
	~Enemy();

	virtual void Action(void);
	virtual void UpDate(void) = 0;
	virtual void Draw_(void) = 0;
	virtual bool Initialize(void);
	virtual void SetPos(const Vector2I& pos,int z);

	// ÌßÚ²Ô°‚Ìe’e‚Æ‚Ì“–‚½‚è”»’è
	virtual bool CheckHitPlayerBullet(const std::vector<std::shared_ptr<BulletBase>>& playerBullets);
	// ÌßÚ²Ô°‚É©•ª‚Ì’e‚ª“–‚½‚Á‚½‚©‚Ì“–‚½‚è”»’è
	virtual bool CheckHitMyBulletToPlayer(std::vector<std::shared_ptr<BulletBase>>& bullets);
	// ©•ª‚Éˆê”Ô‹ß‚¢ƒvƒŒƒCƒ„[‚ğ‹——£‚ğŒvZ‚µ‚Ä‚©‚ç‚Ìæ“¾
	virtual std::shared_ptr<ControlledPlayer> SearchNearestPlayer(void);
	// ©•ª‚Éˆê”Ô‹ß‚¢ƒvƒŒƒCƒ„[‚ğŒvZ‚È‚µ‚Åæ“¾
	// ‚¢‚¿‚¢‚¿ŒvZ•‰‰×‚ğ‚©‚¯‚½‚­‚È‚¢‚½‚ß
	virtual std::shared_ptr<ControlledPlayer> GetNearestPlayer(void);
	// AIº×²ÀŞ°æ“¾ŠÖ”
	virtual const std::unique_ptr<AICollider>& GetAICollider(void);
	// “G1‘Ì‚ÌAI¼½ÃÑæ“¾ŠÖ”
	virtual const std::shared_ptr<AIBase>& GetAISystem(void)
	{
		return aiSystem_;
	}
	// ©g‚ÌŒÅ—L¯•Ê”Ô†‚Ìæ“¾
	virtual const int& GetId(void)
	{
		return id_;
	}

	// AIstateæ“¾ŠÖ”
	virtual AIState& GetAIState(void)
	{
		return AIstate_;
	}

	// ’‡ŠÔ‚ÌAIº×²ÀŞ°‚Æ“–‚½‚Á‚½‚©‚ÌÌ×¸Şæ“¾
	virtual bool& GetisHitAICollider(void)
	{
		return isHitAICollider_;
	}

	// e’e‚Ì’Ç‰Á
	void AddBullet(std::vector<std::shared_ptr<BulletBase>>& bullets);

	void SetisBehindPlayer(bool& flg);
	const bool& GetisBehindPlayer(void)
	{
		return isBehindPlayer_;
	}

	bool& GetFriendlyFireFlag(void)
	{
		return friendlyFireFlag_;
	}

	virtual void AddMuzzleFlashAnimationCount(float cnt)
	{
		muzzleFlashAnimationCount_ += cnt;
	}

	float& GetmuzzleFlashAnimationCount(void)
	{
		return muzzleFlashAnimationCount_;
	}
private:

protected:
	// “G‚ÌŒÅ—L¯•Ê”Ô†(¶¬‚³‚ê‚é‚Æ1‰ÁZ)
	static int enemyNo_;
	// ©•ª©g‚ÌŒÅ—L¯•Ê”Ô†
	int id_;
	// À²Ìß•Ê‚ÌÀŞÒ°¼Ş—¦
	// “GŠF‚ÍHP‚ğ“¯‚¶100‚É‚µ‚Ä‚¨‚¢‚ÄAÀŞÒ°¼Ş—¦‚ÅH‚ç‚¤ÀŞÒ°¼Ş‚ÌŠ„‡‚ğŒvZ‚·‚é
	float damageRate_;
	// Še“G‚Ì’e‚ÌUŒ‚—Í
	float attackRate_;
	// AI½Ã°Ä•Ï”
	AIState AIstate_;
	// ’‡ŠÔ‚ÌAIº×²ÀŞ°‚É“–‚½‚Á‚½‚©‚ÌÌ×¸Ş
	bool isHitAICollider_;
	// ÌßÚ²Ô°‚Ì”wŒã‚É‚¢‚éÌ×¸Ş
	bool isBehindPlayer_;

	// ©•ª‚ª–¡•û‚É“–‚½‚Á‚½Ì×¸Ş(Exoskeleton‚Ì‚İ‚É‘Î‚µ‚Ä‚µ‚©g—p‚µ‚È‚¢)
	bool friendlyFireFlag_;

	std::vector<std::shared_ptr<ControlledPlayer>>& player_;
	std::shared_ptr<ControlledPlayer> nearestPlayer_;

	std::unique_ptr<AICollider> aiCollider_;
	// “G‚ÌÀ²Ìß‚É‰‚¶‚½AI¼½ÃÑ
	std::shared_ptr<AIBase> aiSystem_;
	// muzzleFlash‚ÌÎß¼Ş¼®İ
	Vector2I muzzleFlashPos_;
	// eŒû‚©‚ço‚émuzzleFlash‚Ì±ÆÒ°¼®İ¶³İÄ
	float muzzleFlashAnimationCount_;

	std::string name_;
};

