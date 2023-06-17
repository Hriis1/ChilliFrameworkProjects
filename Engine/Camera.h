#pragma once
#include "CoordinateTransformer.h"
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
	Vec2<float> getXViewPort() const
	{
		return _currXViewPort;
	}
	Vec2<float> getYViewPort() const
	{
		return _currYViewPort;
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
	Vec2<float> _currXViewPort = {-Graphics::ScreenWidth/2, Graphics::ScreenWidth / 2 };
	Vec2<float> _currYViewPort = { -Graphics::ScreenHeight / 2, Graphics::ScreenHeight / 2 };

};

