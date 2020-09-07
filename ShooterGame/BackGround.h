#pragma once
#include <map>
#define lpBackGround BackGround::GetInstance()

using namespace std;
class BackGround
{
public:
	static BackGround& GetInstance(void)
	{
		static BackGround s_Instance;
		return s_Instance;
	}

	void UpData(void);
	void Draw(void);
private:
	BackGround();
	~BackGround();

	int frame;
};

