#pragma once
#include <string>
#include "Geometory.h"
#include "ObjectType.h"

class Object
{
public:
	Object();
	~Object();
	// •`‰æ
	virtual void Draw(void);
	// Îß¼Ş¼®İ¾¯Ä
	void SetPos(const Vector2I& pos);
	// ‰Šú‰»
	bool Initialize(void);
	// Îß¼Ş¼®İæ“¾
	const Vector2I& GetPos(void)
	{
		return pos_;
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

