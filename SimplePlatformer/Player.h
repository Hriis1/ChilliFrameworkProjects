#pragma once
#include "MainWindow.h"
#include "Colors.h"
#include "Shapes.h"
#include "Entity.h"

#include "Vec2.h"
#include "RectF.h"
#include "Box.h"

constexpr float PLAYER_WIDTH = 40.0f;
constexpr float PLAYER_HEIGHT = 80.0f;
constexpr float PLAYER_SPEED = 80.0f;

class Player : public Box
{
public:
	Player(Vec2<float> pos, MainWindow& wnd):
		_wnd(wnd),
		Box(pos, PLAYER_WIDTH, PLAYER_HEIGHT, BODYTYPE::DYNAMIC, Colors::Blue)
	{

	}

	void update(float deltaTime) override
	{
		if (_wnd.kbd.KeyIsPressed('S'))
		{
			Vec2<float> newPos = getPos() + Vec2<float>(0, -PLAYER_SPEED * deltaTime);
			setPos(newPos);
		}
		if (_wnd.kbd.KeyIsPressed('W'))
		{
			Vec2<float> newPos = getPos() + Vec2<float>(0, +PLAYER_SPEED * deltaTime);
			setPos(newPos);
		}
		if (_wnd.kbd.KeyIsPressed('A'))
		{
			Vec2<float> newPos = getPos() + Vec2<float>(-PLAYER_SPEED * deltaTime, 0);
			setPos(newPos);
		}
		if (_wnd.kbd.KeyIsPressed('D'))
		{
			Vec2<float> newPos = getPos() + Vec2<float>(PLAYER_SPEED * deltaTime, 0);
			setPos(newPos);
		}
	}

private:
	

	MainWindow& _wnd;
};

