#pragma once
#include <map>
#include "Object.h"
#define lpBackGround BackGround::GetInstance()

using namespace std;
class BackGround:
	public Object
{
public:
	BackGround();
	~BackGround();
	bool Initialize(void);
		void Draw(void);
private:
};

