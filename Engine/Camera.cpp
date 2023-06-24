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
	drawable.applyTransformation(
		Mat3<float>::Rotation(_angle) *
		Mat3<float>::Scale(_scale) *
		Mat3<float>::Translation(-_pos._x, -_pos._y)
		
	);
	_ct.draw(drawable);
}
