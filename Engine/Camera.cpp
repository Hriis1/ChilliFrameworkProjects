#include "Camera.h"

Camera::Camera(CoordinateTransformer& ct)
	: _ct(ct)
{
}

void Camera::moveBy(const Vec2<float>& offset)
{
	_pos += offset;
}

void Camera::moveTo(const Vec2<float>& newPos)
{
	_pos = newPos;
}

void Camera::draw(Drawable& drawable)
{
	drawable.translate(-_pos);
	drawable.scale(_scale);
	_ct.draw(drawable);
}
