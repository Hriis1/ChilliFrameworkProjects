#include "Player.h"

void Player::update(float deltaTime)
{
	updateMovement(deltaTime);
	Box::update(deltaTime);
	
}

void Player::updateMovement(float deltaTime)
{
	/*if (_wnd.kbd.KeyIsPressed('S'))
	{
		Vec2<float> moveAmount = Vec2<float>(0, -PLAYER_SPEED * deltaTime);
		Vec2<float> newPos = getPos() + moveAmount;
		setPos(newPos);
		_rect.moveBy(moveAmount);
	}
	if (_wnd.kbd.KeyIsPressed('W'))
	{
		Vec2<float> moveAmount = Vec2<float>(0, PLAYER_SPEED * deltaTime);
		Vec2<float> newPos = getPos() + moveAmount;
		setPos(newPos);
		_rect.moveBy(moveAmount);
	}*/

	if (_wnd.kbd.KeyIsPressed('A') || _wnd.kbd.KeyIsPressed('D'))
	{
		if (_wnd.kbd.KeyIsPressed('A'))
		{
			_velocity._x = -PLAYER_SPEED * deltaTime;
		}
		if (_wnd.kbd.KeyIsPressed('D'))
		{
			_velocity._x = PLAYER_SPEED * deltaTime;
		}
	}
	else
	{
		_velocity._x = 0.0f;
	}


	//Jumping
	if (_wnd.kbd.KeyIsPressed(VK_SPACE) && _grounded)
	{
		_velocity._y = 5.0f;
		_grounded = false;
	}
}
