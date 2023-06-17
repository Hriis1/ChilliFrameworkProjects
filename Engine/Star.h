#pragma once

#include "Entity.h"
#include "Colors.h"
#include "Shapes.h"

class Star : public Entity
{
public:
	Star(Vec2<float> pos, float radius, float innerRatio, int nFlares, Color c)
		: Entity(ShapeMaker::makeStar(radius, radius* innerRatio, nFlares), pos, c), _radius(radius)
	{

	}

	//getters
	float getRadius() const
	{
		return _radius;
	}

private:
	float _radius;
};
