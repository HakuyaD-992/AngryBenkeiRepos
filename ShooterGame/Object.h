#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Geometory.h"
#include "ObjectType.h"

class ControlledPlayer;
<<<<<<< HEAD

class Object
{
public:
	Object(std::shared_ptr<ControlledPlayer>& player);
=======
class Object
{
public:
	Object(std::vector<std::shared_ptr<ControlledPlayer>>& player_);
>>>>>>> 56ac109e597b0e82e8d13a0ad1b670f3c322930f
	~Object();
	// •`‰æ
	virtual void Draw(void) = 0;

	// Îß¼Ş¼®İ¾¯Ä
	void SetPos(const Vector2I& pos);
	// ‰Šú‰»
	virtual bool Initialize(void);
	// Îß¼Ş¼®İæ“¾
	const Vector2I& GetPos(void)
	{
		return pos_;
	}

	const ObjectType& GetType(void) const
	{
		return type_;
	}

private:

protected:
	// Îß¼Ş¼®İ
	Vector2I pos_;
	// Šg‘å—¦
	double exRate_;
	// ‰ñ“]—¦
	double rotRate_;
	// µÌŞ¼Şª¸Ä‚ÌÀ²Ìß
	ObjectType type_;
	// ‰æ‘œÊİÄŞÙ
	int imageHandle_;
	// ©g‚ÌµÌŞ¼Şª¸ÄÈ°Ñ
	std::string name_;

<<<<<<< HEAD
	std::shared_ptr<ControlledPlayer>& player_;
=======
	std::vector<std::shared_ptr<ControlledPlayer>>& player_;
>>>>>>> 56ac109e597b0e82e8d13a0ad1b670f3c322930f
};

