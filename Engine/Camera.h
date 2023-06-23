#pragma once
#include "CoordinateTransformer.h"
#include "RectF.h"
#include "MathKEK.h"
class Camera
{
public:
	Camera(CoordinateTransformer& ct);

	void moveBy(const Vec2<float>& offset);
	void moveTo(const Vec2<float>& newPos);

	void draw(Drawable& drawable);
	

	//getters
	Vec2<float> getPos() const
	{
		return _pos;
	}
	float getScale() const
	{
		return _scale;
	}
	float getAngle() const
	{
		return _angle;
	}

	RectF getViewportRect() const
	{
		const float zoom = 1.0f / _scale;

		//Get the rect surrounding the circle made from rotating the original viewportRect(has to be done because of rotation)
		const float diagonalLen = sqrt(sq(float(Graphics::ScreenWidth / 2.0f) * zoom) + sq(float(Graphics::ScreenHeight / 2.0f) * zoom));

		return RectF::fromCenter(_pos, diagonalLen, diagonalLen);
	}

	//setters
	void setScale(float s)
	{
		_scale = s;
	}

	void setAngle(float a)
	{
		_angle = a;
	}
private:
	Vec2<float> _pos = {0.0f, 0.0f};
	float _scale = 1.0f;
	float _angle;
	CoordinateTransformer& _ct;

};

