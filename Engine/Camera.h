#pragma once
#include "CoordinateTransformer.h"
class Camera
{
public:
	Camera(CoordinateTransformer& ct);

	void moveBy(const Vec2<float>& offset);
	void moveTo(const Vec2<float>& newPos);

	void drawPolyLine(std::vector<Vec2<float>> poly, Color c);
	

	//getters
	Vec2<float> getPos() const
	{
		return _pos;
	}
	float getScale() const
	{
		return _scale;
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

