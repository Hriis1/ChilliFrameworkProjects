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

	for (auto ballIter = _balls.begin(); ballIter != _balls.end();)
	{
		ballIter->update();
		if (std::abs(ballIter->getPos()._y) >= 1500.0f)
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
