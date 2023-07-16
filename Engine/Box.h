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
			updatePosition();
		}
	}

	void collideWithBox(Box* other)
	{
		if (_bodyType == BODYTYPE::STATIC) //static boxes dont need collision handling
			return;


		if (_rect.isOverlappingWith(other->_rect)) //check for collision
		{

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
					if (_velocity._y < 0.0f || _rect.bot == other->_rect.top) //coming from the top
					{
						_velocity._y = 0.0f;

						Vec2<float> newPos = Vec2<float>(getPos()._x, other->_rect.top);
						_rect.moveBy(newPos - getPos());
						setPos(newPos);
						_grounded = true;
					}
				}
			}
		}
	}
	
	//getters
	const RectF& getRect() const { return _rect; }
	
private:
	void updatePosition()
	{
		/*if (getPos()._y >= -100.0f)
		{
			_grounded = false;

		}
		else
		{
			_grounded = true;
			_velocity._y = 0.0f;
		}*/

		if (!_grounded)
			_velocity._y += GRAVITY_PULL;

		//update pos based on velocity
		setPos(getPos() + _velocity);

		//update the rects position
		_rect.moveBy(_velocity);
	}

protected:
	RectF _rect;
	BODYTYPE _bodyType;


	bool _grounded = false;
	Vec2<float> _velocity = { 0.0f, 0.0f };
	
};