#include "Box.h"

void Box::update(float deltaTime)
{
	if (_bodyType == BODYTYPE::DYNAMIC) //only update if it is a dynamic box
	{
		updatePosition();
	}
}

void Box::collideWithBox(Box* other)
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
				handleDynamicToRigidBoxCollision(other);
			}
		}
	}
	else //set grounded to false if not colliding with anything
	{
		_grounded = false;
	}
}

void Box::handleDynamicToRigidBoxCollision(Box* other)
{
	float horizontalDistance = std::min(std::abs(_rect.right - other->_rect.left),
		std::abs(_rect.left - other->_rect.right));

	float verticalDistance = std::min(std::abs(_rect.bot - other->_rect.top),
		std::abs(_rect.top - other->_rect.bot));

	if (horizontalDistance < verticalDistance) {
		// Resolve horizontal collision
		float box1CenterX = _rect.left + (_rect.getWidth() / 2.0f);
		float box2CenterX = other->_rect.left + (other->_rect.getWidth() / 2.0f);
		if (box1CenterX < box2CenterX) //coming from the left
		{
			Vec2<float> moveAmount = { other->_rect.left - _rect.right, 0.0f };

			setPos(getPos() + moveAmount);
			_rect.moveBy(moveAmount);
		}
		else if (box1CenterX > box2CenterX) {
			Vec2<float> moveAmount = { other->_rect.right - _rect.left, 0.0f };
			setPos(getPos() + moveAmount);
			_rect.moveBy(moveAmount);
		}
		_velocity._x = 0.0f;
	}
	else {
		// Resolve vertical collision
		if ((_velocity._y < 0.0f || _rect.bot == other->_rect.top)) //coming from the top
		{
			_velocity._y = 0.0f;

			Vec2<float> newPos = Vec2<float>(getPos()._x, other->_rect.top);
			_rect.moveBy(newPos - getPos());
			setPos(newPos);
			_grounded = true;
		}
		else {
			_velocity._y = 0.0f;
			Vec2<float> newPos = Vec2<float>(getPos()._x, other->_rect.bot - _rect.getHeight());
			_rect.moveBy(newPos - getPos());
			setPos(newPos);
		}
	}
}

void Box::updatePosition()
{
	if (!_grounded)
		_velocity._y += GRAVITY_PULL;

	//update pos based on velocity
	setPos(getPos() + _velocity);

	//update the rects position
	_rect.moveBy(_velocity);
}


