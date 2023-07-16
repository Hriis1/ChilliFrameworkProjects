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
#include <Windows.h>

#include "Game.h"
#include "Shapes.h"


Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	_coordTrans(gfx), _camera(_coordTrans), _camControl(wnd, _camera),
	_box({-600.0f,-140.0f}, 1200.0f, 40.0f), 
	_player({100.0f,100.0f},wnd)
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
	//_camControl.update(deltaTime);
	_player.update(deltaTime);
	_player.collideWithBox(&_box);


	//Collision
	const RectF& playerRect = _player.getRect();
	Vec2<float> playerPos = _player.getPos();

	const RectF& boxRect = _box.getRect();

	if (playerRect.isOverlappingWith(boxRect))
	{
		OutputDebugStringA("Player is colliding with the box\n");
	}
	
}

void Game::ComposeFrame()
{
	Drawable boxDr = _box.getDrawable();
	_camera.draw(boxDr);

	Drawable playerDr = _player.getDrawable();
	_camera.draw(playerDr);
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



	const float cameraSpeed = 3.0f;
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
	}
}
