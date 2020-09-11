#pragma once
#include <map>
#include "Object.h"
#define lpBackGround BackGround::GetInstance()

using namespace std;
class BackGround:
	public Object
{
public:
	BackGround(std::vector<std::shared_ptr<ControlledPlayer>>& player);
	~BackGround();
	bool Initialize(void);
		void Draw(void);
private:
};

