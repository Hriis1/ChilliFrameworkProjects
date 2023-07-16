#include "Player.h"

void Player::update(float deltaTime)
{
	Box::update(deltaTime);
	updateMovement(deltaTime);
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
			Vec2<float> moveAmount = Vec2<float>(-PLAYER_SPEED * deltaTime, 0);
			Vec2<float> newPos = getPos() + moveAmount;
			setPos(newPos);
			_rect.moveBy(moveAmount);
		}
		if (_wnd.kbd.KeyIsPressed('D'))
		{
			Vec2<float> moveAmount = Vec2<float>(PLAYER_SPEED * deltaTime, 0);
			Vec2<float> newPos = getPos() + moveAmount;
			setPos(newPos);
			_rect.moveBy(moveAmount);
		}
	}
}
