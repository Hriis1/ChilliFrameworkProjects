#pragma once
#include "Colors.h"
#include "Shapes.h"
#include "Entity.h"

#include "RectF.h"

class Box : public Entity
{
public:
	Box(Vec2<float> pos, float width, float height, Color c = Colors::Red)
		: Entity(ShapeMaker::makeRectangle(width, height), pos, c), rect(pos, width, height)
	{

	}

private:
	RectF rect;
	
};
