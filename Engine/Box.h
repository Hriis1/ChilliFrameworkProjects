#pragma once
#include "Colors.h"
#include "Shapes.h"
#include "Entity.h"

#include "RectF.h"


constexpr float GRAVITY_PULL = 7.0f;
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
			if (getPos()._y >= -100.0f)
			{
				setPos(getPos() + Vec2<float>(0.0f, -GRAVITY_PULL));
			}
		}
	}

	void collideWithBox(Box* other)
	{
		if (_bodyType == BODYTYPE::STATIC) //static boxes dont need collision handling
			return;


		if (_bodyType == BODYTYPE::RIGID)
		{
			if (other->_bodyType == BODYTYPE::DYNAMIC) //1st box is rigid 2nd is dynamic
			{

			}
		}
		else if (_bodyType == BODYTYPE::DYNAMIC)
		{
			if (other->_bodyType == BODYTYPE::DYNAMIC) //both boxes are dynamic
			{
				//TODO maybe
			}
			else if (other->_bodyType == BODYTYPE::RIGID) //1st box is dynamic 2nd is rigid
			{

			}
		}
		
	}
	
	//getters
	const RectF& getRect() const { return _rect; }
	

protected:
	RectF _rect;
	BODYTYPE _bodyType;


	bool grounded = false;
	
};