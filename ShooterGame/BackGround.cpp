#include <DxLib.h>
#include "ImageManager.h"
#include "BackGround.h"

void BackGround::UpData(void)
{
	frame++;
}

void BackGround::Draw(void)
{
	DrawGraph(0, 0, lpImage.GetDivID("sky")[(frame/5) % 6], true);
	DrawGraph(0, 0, lpImage.GetDivID("sky_effect")[(frame/5) % 6], true);
}

BackGround::BackGround()
{
	lpImage.LoadDiv("sky", Vector2I(800, 600), Vector2I(3, 2));
	lpImage.LoadDiv("sky_effect", Vector2I(800, 600), Vector2I(3, 2));
	frame = 0;
}

BackGround::~BackGround()
{
}
