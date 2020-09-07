#pragma once
#include <string>
#include <vector>
#include "Geometory.h"
#include "ObjectType.h"

class Object
{
public:
	Object();
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
};

