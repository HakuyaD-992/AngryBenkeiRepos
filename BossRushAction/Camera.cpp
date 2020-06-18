#include "Camera.h"
#include "SceneShift.h"

Camera::Camera(Vector2 pos)
{
	this->pos = pos;
	fixedPos = { lpScene.GetScreenSize().x / 2,0 };
}

Camera::~Camera()
{
}

void Camera::UpDate(const Vector2 & pos)
{
	this->pos.x = fixedPos.x - pos.x;
}
