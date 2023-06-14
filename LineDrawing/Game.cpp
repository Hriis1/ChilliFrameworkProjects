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

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	_coordTrans(gfx), _e1(ShapeMaker::makeStar(150, 75))
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
	const int speed = 3;
	if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		_e1.translateBy({0, -speed});
	}
	if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		_e1.translateBy({0, speed});
	}
	if (wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		_e1.translateBy({-speed, 0});
	}
	if (wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		_e1.translateBy({speed, 0 });
	}

	while (!wnd.mouse.IsEmpty())
	{
		const auto e = wnd.mouse.Read();

		if (e.GetType() == Mouse::Event::Type::WheelUp)
			_e1.setScale(_e1.getScale() * 1.1f);
		else if(e.GetType() == Mouse::Event::Type::WheelDown)
			_e1.setScale(_e1.getScale() * 0.9f);
	}
}

void Game::ComposeFrame()
{
	if(wnd.mouse.LeftIsPressed())
		gfx.drawLine(Vec2<float>(100, 100), Vec2<float>(wnd.mouse.GetPosX(), wnd.mouse.GetPosY()), Colors::White);


	_coordTrans.drawPolyLine(_e1.getPolyLine(), Colors::Red);
}
