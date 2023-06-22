#pragma once

#include "Entity.h"
#include "Colors.h"
#include "Shapes.h"
#include "RectF.h"

class Star : public Entity
{
public:
	Star(Vec2<float> pos, float radius, float innerRatio, int nFlares, Color c, float colorFreq, float colorPhase, float scaleOffset, float maxChange, float rotationSpeed)
		: Entity(ShapeMaker::makeStar(radius, radius* innerRatio, nFlares), pos, c), _radius(radius),
		_colorFreqFactor(colorFreq * 2.0f * 3.14159f), _colorPhase(colorPhase), _baseCol(c),
		_scaleOffset(scaleOffset), _maxChange(maxChange), _rotationSpeed(rotationSpeed)
	{

	}
	void Update(float deltaTime)
	{
		_time += deltaTime;
		UpdateColor();
		UpdateScale();
		UpdateRotation();
	}

	//getters
	float getRadius() const
	{
		return _radius * getScale();
	}
	float getMaxRadius() const
	{
		return _radius + _radius * _maxChange;
	}

	RectF getBoundingRect() const
	{
		return RectF::fromCenter(getPos(), getRadius(), getRadius());
	}

private:
	void UpdateColor()
	{
		Color c;
		int offset = int(127.0f * sin(_colorFreqFactor * _time + _colorPhase)) + 128;
		int r = _baseCol.GetR();
		int g = _baseCol.GetG();
		int b = _baseCol.GetB();
		c.SetR(std::min(_baseCol.GetR() + offset, 255));
		c.SetG(std::min(_baseCol.GetG() + offset, 255));
		c.SetB(std::min(_baseCol.GetB() + offset, 255));
		setColor(c);
	}

	void UpdateScale()
	{
		float offset = (sin(_time + _scaleOffset)) * _maxChange;
		setScale(1.0f + offset);
	}

	void UpdateRotation()
	{
		setAngle(_rotationSpeed * _time);
	}
private:
	float _radius;
	float _maxChange;
	Color _baseCol;
	float _colorFreqFactor;
	float _colorPhase;
	float _scaleOffset;
	float _rotationSpeed;
	float _time = 0.0f;
};
