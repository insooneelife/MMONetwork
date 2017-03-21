#include "Camera2D.h"

#include <iostream>

std::unique_ptr<Camera2D> Camera2D::instance = nullptr;

void Camera2D::staticInit(float screenX, float screenY)
{
	instance.reset(new Camera2D(screenX, screenY));
}

Camera2D::Camera2D(float screenX, float screenY)
	:
	_screenX(screenX),
	_screenY(screenY),
	_origin(0, 0),
	_axisX(1, 0),
	_axisY(0, 1),
	_scale(100.0f, 100.0f)
{}

Vec2 Camera2D::worldToScreen(const Vec2& pos)
{
	Vec2 convertPos = pointToLocalSpace(pos, _axisX, _axisY, _origin);

	//create a transformation matrix
	C2DMatrix matTransform;
	//scale
	if ((_scale.x != 1.0) || (_scale.y != 1.0))
		matTransform.scale(_scale.x, _scale.y);
	matTransform.transform(convertPos);


	convertPos = Vec2(_screenX / 2 + convertPos.x, _screenY / 2 - convertPos.y);
	return convertPos;
}

Vec2 Camera2D::screenToWorld(const Vec2& mpos)
{
	Vec2 convertPos = Vec2(mpos.x - _screenX / 2, -mpos.y + _screenY / 2) + _origin;
	return convertPos;
}
