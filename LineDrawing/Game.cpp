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
	_rng(std::random_device()()),_coordTrans(gfx), _camera(_coordTrans)
{
	/*_entities.emplace_back(ShapeMaker::makeStar(100.0f, 50.0f), Vec2<float>(460.0f, 0.0f));
	_entities.emplace_back(ShapeMaker::makeStar(150.0f, 50.0f), Vec2<float>(150.0f, 300.0f));
	_entities.emplace_back(ShapeMaker::makeStar(100.0f, 50.0f), Vec2<float>(250.0f, -200.0f));
	_entities.emplace_back(ShapeMaker::makeStar(150.0f, 50.0f), Vec2<float>(-250.0f, 200.0f));
	_entities.emplace_back(ShapeMaker::makeStar(100.0f, 50.0f), Vec2<float>(0.0f, 0.0f));
	_entities.emplace_back(ShapeMaker::makeStar(200.0f, 50.0f), Vec2<float>(-150.0f, -300.0f));
	_entities.emplace_back(ShapeMaker::makeStar(100.0f, 50.0f), Vec2<float>(400.0f, 300.0f));*/

	generateStars();
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
	/*const int speed = 3;
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
	*/
	while (!wnd.mouse.IsEmpty())
	{
		const auto e = wnd.mouse.Read();

		if (e.GetType() == Mouse::Event::Type::WheelUp)
			_camera.setScale(_camera.getScale() * 1.1f);
		else if(e.GetType() == Mouse::Event::Type::WheelDown)
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

void Game::ComposeFrame()
{
	/*if(wnd.mouse.LeftIsPressed())
		gfx.drawLine(Vec2<float>(100, 100), Vec2<float>(wnd.mouse.GetPosX(), wnd.mouse.GetPosY()), Colors::White);*/

	const auto viewPort = _camera.getViewportRect();
	for (const auto& e : _stars)
	{
		Drawable dr = e.getDrawable();

		//Draw only the objects that are visible by the camera
		if(viewPort.isOverlappingWith(e.getBoundingRect()))
			_camera.draw(dr);
	}
}





void Game::generateStars()
{
	int xMin = -5000;
	int xMax = 5000;

	int yMin = -3000;
	int yMax = 3000;

	float maxStarRad = 300.0f;

	std::uniform_int_distribution<int> xDist(xMin, xMax);
	std::uniform_int_distribution<int> yDist(yMin, yMax);
	std::uniform_real_distribution<float> outerRDist(100.0f, maxStarRad);
	std::uniform_real_distribution<float> innerRatioDist(0.2f, 0.8f);
	std::uniform_int_distribution<int> pointsDist(3, 8);

	while(_stars.size() < 200)
	{
		Vec2<float> pos = Vec2<float>(xDist(_rng), yDist(_rng));
		float outerRad = outerRDist(_rng);
		float innerRatio = innerRatioDist(_rng);

		if (std::any_of(_stars.begin(), _stars.end(), [&](const Star& star)
			{
				return (star.getPos() - pos).getLenght() < outerRad + star.getRadius();
			}))
		{
			continue;
		}
			_stars.emplace_back(Star(pos, outerRad,innerRatio,pointsDist(_rng), Colors::White));
	}

}
