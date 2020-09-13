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
<<<<<<< HEAD
	BackGround(std::shared_ptr<ControlledPlayer>& player);
=======
	BackGround(std::vector<std::shared_ptr<ControlledPlayer>>& player);
>>>>>>> 56ac109e597b0e82e8d13a0ad1b670f3c322930f
	~BackGround();
	bool Initialize(void);
		void Draw(void);
private:
};

