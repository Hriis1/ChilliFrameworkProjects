#pragma once
#include <random>

#include "Ball.h"

class SpawnPoint
{
public:
	SpawnPoint(std::vector<Ball>& balls, float radius, Vec2<float> pos, float minVelX, float maxVelX, float yVel, float period, Color c = Colors::Red)
		: _balls(balls), _ballRadius(radius), _pos(pos), _xVelDist(minVelX, maxVelX), _yVel(yVel), _period(period), _color(c)
	{

	}

	void update(float deltaTime)
	{
		_time += deltaTime;
		if (_time >= _period)
		{
			_time -= _period;
			_balls.emplace_back(_pos, _ballRadius, Vec2<float>(_xVelDist(_rng), _yVel), _color);
		}
	}
private:
	std::vector<Ball>& _balls;
	float _ballRadius;
	Vec2<float> _pos;
	std::mt19937 _rng = std::mt19937(std::random_device()());
	std::uniform_real_distribution<float> _xVelDist;
	float _yVel;
	float _period;
	Color _color;
	float _time = 0;
	
};