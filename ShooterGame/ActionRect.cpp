#include <DxLib.h>

#include "ActionRect.h"

ActionRect::ActionRect()
{
	boxcol_ = 0xffffff;
	center_ = { data_.begin_.x + data_.size_.x / 2,data_.begin_.y + data_.size_.y / 2 };

}

ActionRect::~ActionRect()
{
}

void ActionRect::Draw(const Vector2I& player)
{
	switch (data_.type_)
	{
	case RectType::Attack:
		// red
		boxcol_ = 0xff0000;
		break;

	case RectType::Damage:
		// blue
		boxcol_ = 0x0000ff;
		break;

	case RectType::Max:
		// white
		boxcol_ = 0xffffff;
		break;
	default:
		boxcol_ = 0x000000;
		break;
	}

	auto begin = Vector2I(center_.x - (data_.size_.x / 2), center_.y - (data_.size_.y / 2));
	auto end = Vector2I(center_.x + (data_.size_.x / 2), center_.y + (data_.size_.y / 2));

	DrawBox(player.x + begin.x,
		player.y + begin.y,
		player.x + end.x,
		player.y + end.y, boxcol_, false);
}
