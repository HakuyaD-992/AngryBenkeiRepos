#include "StageLoader.h"

std::once_flag StageLoader::onceflag;
StageLoader* StageLoader::stageLoaderIns = nullptr;

void StageLoader::Destroy(void)
{
	if (stageLoaderIns != nullptr)
	{
		delete stageLoaderIns;
	}
	stageLoaderIns = nullptr;
}

StageLoader::StageLoader()
{
}


StageLoader::~StageLoader()
{
}

void StageLoader::Create(void)
{
	stageLoaderIns = new StageLoader();
}
