#pragma once
#include "Colors.h"
#include "Shapes.h"
#include "Entity.h"

#include "RectF.h"



class Box : public Entity
{
public:
	Box(Vec2<float> pos, float width, float height, BODYTYPE bodyType = BODYTYPE::RIGID, Color c = Colors::Red)
		: Entity(ShapeMaker::makeRectangle(width, height), pos, c), rect(pos, width, height), _bodyType(bodyType)
	{

	}

	virtual void update(float deltaTime)
	{
		if (_bodyType == BODYTYPE::DYNAMIC) //only update if it is a dynamic box
		{

		}
	}

protected:
	RectF rect;
	BODYTYPE _bodyType;
	
};
