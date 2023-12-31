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
	_coordTrans(gfx), _camera(_coordTrans), _camControl(wnd, _camera),
	_sPoint(_balls, 20.0f, {-100.0f, -200.0f}, -2.0f, 0.5f, 2.0f, 0.5f),
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
	_t += deltaTime;
	_camControl.update(deltaTime);

	if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		_plank.moveFreeY(-2.0f);
	}
	if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		_plank.moveFreeY(2.0f);
	}

	_sPoint.update(deltaTime);

	for (auto ballIter = _balls.begin(); ballIter != _balls.end();)
	{
		ballIter->update(deltaTime);

		const Vec2<float> ballPos = ballIter->getPos();

		if (ballIter != _balls.end())
		{
			const auto plankVector = _plank.getPlankSurfaceVector();
			const auto plankPts = _plank.getPoints();
			const auto plankNormal = plankVector.getRotatedNegative90Degrees();
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

	_star = ShapeMaker::makeStar(150.0f, 60.0f);
	const float theta = _t * PI;

	for (auto& vert : _star)
	{
		vert.Rotate(theta);
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

	Drawable starDrawable = Drawable(_star, Colors::Yellow);
	_camera.draw(starDrawable);
}
