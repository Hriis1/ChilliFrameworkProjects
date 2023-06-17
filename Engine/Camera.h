#pragma once
#include "CoordinateTransformer.h"
#include "RectF.h"
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

	RectF getViewportRect() const
	{
		const float zoom = 1.0f / _scale;

		return RectF::fromCenter(_pos, float(Graphics::ScreenWidth / 2.0f) * zoom, float(Graphics::ScreenHeight / 2.0f) * zoom);
	}

	//setters
	void setScale(float s)
	{
		_scale = s;
	}
private:
	Vec2<float> _pos = {0.0f, 0.0f};
	float _scale = 1.0f;
	CoordinateTransformer& _ct;

};

