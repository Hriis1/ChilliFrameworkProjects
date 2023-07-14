#pragma once
#include "Colors.h"
#include "Shapes.h"
#include "Entity.h"

#include "RectF.h"



class Box : public Entity
{
public:
	Box(Vec2<float> pos, float width, float height, BODYTYPE bodyType = BODYTYPE::RIGID, Color c = Colors::Red)
		: Entity(ShapeMaker::makeRectangle(width, height), pos, c), _rect(Vec2<float>(pos._x, pos._y + height), Vec2<float>(pos._x + width, pos._y)), _bodyType(bodyType)
	{

	}

	virtual void update(float deltaTime)
	{
		if (_bodyType == BODYTYPE::DYNAMIC) //only update if it is a dynamic box
		{

		}
	}
	
	//getters
	const RectF& getRect() const { return _rect; }
	

protected:
	RectF _rect;
	BODYTYPE _bodyType;
	
};
