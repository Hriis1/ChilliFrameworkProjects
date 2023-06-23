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
#include "MathKEK.h"
#include "Mat2.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	_rng(std::random_device()()),_coordTrans(gfx), _camera(_coordTrans),
	_camControl(wnd, _camera)
{
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
	const float deltaTime = _ft.Mark();
	_camControl.update(deltaTime);

	for (auto& star : _stars)
	{
		star.Update(deltaTime);
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
	

	auto star = ShapeMaker::makeStar(100.0f, 50.0f);
	const Mat2<float> transformation1 = Mat2<float>::Rotation(0.3f);
	const Mat2<float> transformation2 = Mat2<float>::Scale(2.0f);
	const Mat2<float> transformation3 = Mat2<float>::FlipY();
	Mat2<float> transformCat = transformation3 * transformation2 * transformation1;
	//transformCat = transformCat * transformation3;
	for (auto& v : star)
	{
		v = transformCat * v;
	}
	Drawable dr = Drawable{ star, Colors::Green };
	_camera.draw(dr);
}





void Game::generateStars()
{
	int xMin = -5000;
	int xMax = 5000;

	int yMin = -3000;
	int yMax = 3000;

	float maxStarRad = 300.0f;

	float minRotSpeed = -2.0f * PI;
	float maxRotSpeed = 2.0f * PI;

	std::uniform_int_distribution<int> xDist(xMin, xMax);
	std::uniform_int_distribution<int> yDist(yMin, yMax);
	std::uniform_real_distribution<float> outerRDist(100.0f, maxStarRad);
	std::uniform_real_distribution<float> innerRatioDist(0.2f, 0.8f);
	std::uniform_int_distribution<int> pointsDist(3, 8);
	std::uniform_real_distribution<float> colorFreqDist(0.6f, 4.0f);
	std::uniform_real_distribution<float> phaseDist(0.0f, 2.0f * 3.14f);
	std::uniform_real_distribution<float> scaleOffsetDist(0.0f, 30.0f);
	std::uniform_real_distribution<float> rotationSpeedDist(minRotSpeed, maxRotSpeed);
	float maxRadiusChange = 0.6f;

	const Color colors[] = { Colors::Red,Colors::Blue,Colors::Cyan,Colors::Yellow,Colors::Magenta,Colors::Green };
	std::uniform_int_distribution<size_t> colorSampler(0, std::end(colors) - std::begin(colors));

	while(_stars.size() < 100)
	{
		Vec2<float> pos = Vec2<float>(xDist(_rng), yDist(_rng));
		float outerRad = outerRDist(_rng);
		float innerRatio = innerRatioDist(_rng);

		if (std::any_of(_stars.begin(), _stars.end(), [&](const Star& star)
			{
				return (star.getPos() - pos).getLenght() < outerRad + outerRad * maxRadiusChange + star.getMaxRadius();
			}))
		{
			continue;
		}
			const Color c = colors[colorSampler(_rng)];
			_stars.emplace_back(Star(pos, outerRad,innerRatio,pointsDist(_rng), c,colorFreqDist(_rng), phaseDist(_rng), scaleOffsetDist(_rng), maxRadiusChange, rotationSpeedDist(_rng)));
	}

}
