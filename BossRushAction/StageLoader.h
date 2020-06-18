#pragma once
// stage load

#include <mutex>

#define lpStageLoader StageLoader::getInstance()

class StageLoader
{
public:
	static void Destroy(void);
	static StageLoader &getInstance(void)
	{
		std::call_once(onceflag, Create);
		return *stageLoaderIns;
	}

private:
	StageLoader();
	~StageLoader();

	static std::once_flag onceflag;
	static StageLoader* stageLoaderIns;

	static void Create(void);
};

