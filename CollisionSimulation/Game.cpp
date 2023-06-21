/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "Shapes.h"
#include "MathKEK.H"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	_sPoint(_balls, 20.0f, {-100.0f, -200.0f}, -2.0f, 0.5f, 2.0f, 0.5f),
	_coordTrans(gfx), _camera(_coordTrans),
	_plank({ 0.0f,200.0f }, -380.0f, -100.0f, 290.0f)
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	const float deltaTime = _ft.Mark();
	updateCamera();

	if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		_plank.moveFreeY(-2.0f);
	}
	if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		_plank.moveFreeY(2.0f);
	}

	_sPoint.update(deltaTime);

	const auto plankPts = _plank.getPoints();
	const float deltax = plankPts.second._x - plankPts.first._x;
	const float deltay = plankPts.second._y - plankPts.first._y;
	for (auto ballIter = _balls.begin(); ballIter != _balls.end();)
	{
		ballIter->update(deltaTime);

		Vec2<float> plankNormal;
		const Vec2<float> ballPos = ballIter->getPos();

		if (ballIter != _balls.end())
		{
			// get the plank normal in the direction of the ball
			//plank is a horizontal line
			if (deltay == 0)
			{
				//set the normal to either 0 1 or 0 -1 depending on if the ball is above or below the plank (the normal must be in the direction of the ball)
				plankNormal = { 0.0f, ballPos._y > plankPts.first._y ? 1.0f : -1.0f };
			}
			//plank is a vertical line
			else if (deltax == 0)
			{
				//the normal must be in the direction of the ball
				plankNormal = { ballPos._x > plankPts.first._x ? 1.0f : -1.0f, 0.0f  };
			}
			else
			{
				const float m = deltay / deltax;
				const float w = -deltax / deltay;

				const float b = plankPts.first._y - m * plankPts.first._x;
				const float p = ballPos._y - w * ballPos._x;

				const float x = (p - b) / (m - w);
				const auto y = m * x + b;

				plankNormal = (ballPos - Vec2<float>{x, y}).normalize();
			}
			
			//Only check for collision if the ball is going towards the plank
			if(plankNormal.dot(ballIter->getVel()) < 0.0f)
			{ 
				//if this is true we have a collision between the ball and the plank
				if (pointLineDistance(plankPts.first, plankPts.second, ballPos) < ballIter->getRadius())
				{
					ballIter->setColor(Colors::Green);
					const Vec2<float> w = _plank.getPlankSurfaceVector().getNormalized();
					const Vec2<float> v = ballIter->getVel();
					ballIter->setVel(w * 2 * (v.dot(w)) - v);

				}
			}
			
		}

		if (std::abs(ballPos._y) >= 1500.0f)
		{
			ballIter = _balls.erase(ballIter);
		}
		else
		{
			ballIter++;
		}

		
		
	}
	
}

void Game::ComposeFrame()
{
	Drawable plankDrawable = _plank.getDrawable();
	_camera.draw(plankDrawable);


	for (auto ballIter = _balls.begin(); ballIter != _balls.end(); ballIter++)
	{
		Drawable ballDrawable = ballIter->getDrawable();
		_camera.draw(ballDrawable);
	}
}

void Game::updateCamera()
{
	while (!wnd.mouse.IsEmpty())
	{
		const auto e = wnd.mouse.Read();

		if (e.GetType() == Mouse::Event::Type::WheelUp)
			_camera.setScale(_camera.getScale() * 1.1f);
		else if (e.GetType() == Mouse::Event::Type::WheelDown)
			_camera.setScale(_camera.getScale() * 0.9f);
	}



	/*const float cameraSpeed = 3.0f;
	if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		_camera.moveBy(Vec2<float>(0.0f, -cameraSpeed));
	}
	if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		_camera.moveBy(Vec2<float>(0.0f, cameraSpeed));
	}
	if (wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		_camera.moveBy(Vec2<float>(-cameraSpeed, 0.0f));
	}
	if (wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		_camera.moveBy(Vec2<float>(cameraSpeed, 0.0f));
	}*/
}
