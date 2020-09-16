#pragma once
#include <map>
#include <memory>
#include "Object.h"

#define lpBackGround BackGround::GetInstance()

using namespace std;
class ControlledPlayer;

class BackGround:
	public Object
{
public:
	BackGround(std::shared_ptr<ControlledPlayer>& player);
	~BackGround();
	bool Initialize(void);
	void Draw(void);
private:

	Vector2I scoreUIPos_;
};

