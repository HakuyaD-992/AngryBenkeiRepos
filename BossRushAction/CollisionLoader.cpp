#include "CollisionLoader.h"

std::once_flag CollisionLoader::onceflag;
CollisionLoader* CollisionLoader::colLoaderIns = nullptr;

void CollisionLoader::Destroy(void)
{
	if (colLoaderIns != nullptr)
	{
		delete colLoaderIns;
	}
	colLoaderIns = nullptr;
}

void CollisionLoader::LoadPlayerCollider(PlayerRectData & playerData,
										 const ANIMATION& pAnimation,
										 const AnimationLevel& animlevel)
{
	for(int level = 0;level < animlevel;level++)
	{
		playerDataHeader[pAnimation].emplace_back();
		for (int frame = 0;
			frame < playerData[pAnimation].playerAnimLevelData[level].playerRectData.size();
			frame++)
		{
			std::string playerDataHeaderFileName
				= playerData[pAnimation].playerAnimLevelData[level].playerRectData[frame].fileName
				+ "_header.map";

			fopen_s(&playerDataHeaderFile, playerDataHeaderFileName.c_str(), "rb");
			for (int flag = R_State_Damage; flag < R_State_Max; flag++)
			{
				if (playerDataHeader[pAnimation][level].size() <= 0)
				{
					playerDataHeader[pAnimation][level].resize(playerData[pAnimation].playerAnimLevelData[level].playerRectData.size());
				}
				fread(&playerDataHeader[pAnimation][level][frame].dataNum[flag], sizeof(int), 1, playerDataHeaderFile);
			}
			fclose(playerDataHeaderFile);

		}
	}

	for (int level = 0; level < animlevel; level++)
	{
		for (int frame = 0;
			frame < playerData[pAnimation].playerAnimLevelData[level].playerRectData.size();
			frame++)
		{
			std::string playerDataFileName =
				playerData[pAnimation].playerAnimLevelData[level].playerRectData[frame].fileName
				+ ".map";

			fopen_s(&playerDataFile, playerDataFileName.c_str(), "rb");

			for (int flag = R_State_Damage; flag < R_State_Max; flag++)
			{
				playerData[pAnimation].playerAnimLevelData[level].playerRectData[frame].pos[flag].resize
				(playerDataHeader[pAnimation][level][frame].dataNum[flag]);

				playerData[pAnimation].playerAnimLevelData[level].playerRectData[frame].size[flag].resize
				(playerDataHeader[pAnimation][level][frame].dataNum[flag]);

				playerData[pAnimation].playerAnimLevelData[level].playerRectData[frame].rectNum[flag]
					= playerDataHeader[pAnimation][level][frame].dataNum[flag];

				for (int rectNum = 0; rectNum < playerDataHeader[pAnimation][level][frame].dataNum[flag];
					rectNum++)
				{
					fread(&playerData[pAnimation].playerAnimLevelData[level].playerRectData[frame].pos[flag][rectNum],
						sizeof(Vector2), 1, playerDataFile);

					fread(&playerData[pAnimation].playerAnimLevelData[level].playerRectData[frame].size[flag][rectNum],
						sizeof(Vector2), 1, playerDataFile);
				}
			}
			fclose(playerDataFile);

		}
	}
}

void CollisionLoader::LoadEnemyCollider(EnemyRectData & enemyData,
										const EnemyAnimation & eAnimation,
										const ENEMYTYPE & eType)
{
	enemyDataHeader[eAnimation][eType].resize
	(enemyData[eType].enemyAnimationRectData[eAnimation].enemyFrameRectData.size());

	for (int frame = 0;
		frame < enemyData[eType].enemyAnimationRectData[eAnimation].enemyFrameRectData.size();
		frame++)
	{
		std::string enemyHeaderFileName
			= enemyData[eType].enemyAnimationRectData[eAnimation].enemyFrameRectData[frame].fileName
			+ "_header.map";

		fopen_s(&enemyDataHeaderFile, enemyHeaderFileName.c_str(), "rb");
		for (int flag = R_State_Damage; flag < R_State_Max; flag++)
		{
			fread(&enemyDataHeader[eAnimation][eType][frame].dataNum[flag], sizeof(int), 1, enemyDataHeaderFile);
		}
		fclose(enemyDataHeaderFile);
	}

	for (int frame = 0;
		frame < enemyData[eType].enemyAnimationRectData[eAnimation].enemyFrameRectData.size();
		frame++)
	{

		std::string enemyDataFileName =
			enemyData[eType].enemyAnimationRectData[eAnimation].enemyFrameRectData[frame].fileName
			+ ".map";

		fopen_s(&enemyDataFile, enemyDataFileName.c_str(), "rb");

		for (int flag = R_State_Damage; flag < R_State_Max; flag++)
		{
			// rect position
			enemyData[eType].enemyAnimationRectData[eAnimation].enemyFrameRectData[frame].pos[flag].resize
			(enemyDataHeader[eAnimation][eType][frame].dataNum[flag]);

			// rect size
			enemyData[eType].enemyAnimationRectData[eAnimation].enemyFrameRectData[frame].size[flag].resize
			(enemyDataHeader[eAnimation][eType][frame].dataNum[flag]);

			// rect num
			enemyData[eType].enemyAnimationRectData[eAnimation].enemyFrameRectData[frame].rectNum[flag]
				= enemyDataHeader[eAnimation][eType][frame].dataNum[flag];

			for (int rectNum = 0; rectNum < enemyDataHeader[eAnimation][eType][frame].dataNum[flag]; rectNum++)
			{
				fread(&enemyData[eType].enemyAnimationRectData[eAnimation].enemyFrameRectData[frame].pos[flag][rectNum],
					sizeof(Vector2), 1, enemyDataFile);

				fread(&enemyData[eType].enemyAnimationRectData[eAnimation].enemyFrameRectData[frame].size[flag][rectNum],
					sizeof(Vector2), 1, enemyDataFile);
			}
		}
		fclose(enemyDataFile);

	}
}

CollisionLoader::CollisionLoader()
{
}


CollisionLoader::~CollisionLoader()
{
}

void CollisionLoader::Create(void)
{
	if (colLoaderIns == nullptr)
	{
		colLoaderIns = new CollisionLoader();
	}
}
