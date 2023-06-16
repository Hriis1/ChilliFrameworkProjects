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

void Camera::drawPolyLine(std::vector<Vec2<float>> poly, Color c)
{
	for (auto& vert : poly)
	{
		vert *= _scale;
		vert -= _pos;
	}
	_ct.drawPolyLine(std::move(poly), c);
}
