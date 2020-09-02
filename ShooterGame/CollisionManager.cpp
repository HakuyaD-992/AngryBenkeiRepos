#include <DxLib.h>
#include "CollisionManager.h"

void CollisionManager::Load(AnimationRect& actorRect, const std::string& actorname)
{
	for (auto rects = actorRect.begin(); rects != actorRect.end(); rects++)
	{
		// 1ｱﾆﾒｰｼｮﾝの名前
		auto animname = rects->first;
		// ｱｸﾀｰの1ｱﾆﾒｰｼｮﾝ毎にﾙｰﾌﾟで回す
		// 1ﾌﾚｰﾑに何個矩形情報を入れるのかのｻｲｽﾞ情報
		// ﾍｯﾀﾞｰから読み取った情報
		int size = 0;
		// 今現在読み込んでいるﾌｧｲﾙﾊﾝﾄﾞﾙ
		int fileHandle = -1;

		// ﾍｯﾀﾞｰﾌｧｲﾙ読み込みのﾀｰﾝ(1ﾌﾚｰﾑに矩形が何個あるのかの数読み込み)
		std::string fileName = "Data/h/" + actorname + "_" + animname + ".map";
		fileHandle = FileRead_open(fileName.c_str(), false);

		for (int i = 0; i < rects->second.size(); i++)
		{
			FileRead_seek(fileHandle, size_t(sizeof(int) * i), SEEK_SET);
			FileRead_read(&size, sizeof(int), fileHandle);
			for (int s = 0; s < size; s++)
			{
				rects->second[i].emplace_back(std::make_shared<ActionRect>());
			}
		}
		// ﾌｧｲﾙを閉じる(1回目)(ﾍｯﾀﾞｰﾌｧｲﾙ)
		FileRead_close(fileHandle);

		// 矩形ﾃﾞｰﾀの実ﾃﾞｰﾀを読み込む
		fileName = "Data/" + actorname + "_" + animname + ".map";
		fileHandle = FileRead_open(fileName.c_str(), false);
		int size1 = rects->second.size();

		for (int d1 = 0; d1 < size1; d1++)
		{
			int size2 = rects->second[d1].size();
			for (int d2 = 0; d2 < size2; d2++)
			{
				FileRead_seek(fileHandle, size_t(sizeof(RectData) * d2), SEEK_SET);
				FileRead_read(&rects->second[d1][d2]->GetData(), sizeof(RectData), fileHandle);
			}
		}

		// ﾌｧｲﾙを閉じる(2回目)(実ﾃﾞｰﾀ)
		FileRead_close(fileHandle);
	}
}
