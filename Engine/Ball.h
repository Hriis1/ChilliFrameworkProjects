#pragma once
#include "Colors.h"
#include "Shapes.h"
#include "Entity.h"

constexpr float INIT_COLLISION_CD = 0.1f;

class Ball : public Entity
{
public:
	Ball(Vec2<float> pos, float radius, Vec2<float> vel, Color c = Colors::Red)
		: Entity(ShapeMaker::makeStar(radius, radius, 8), pos, c), _vel(vel), _radius(radius)
	{

	}
	void update(float deltaTime)
	{
		translateBy(_vel);

		if (!_canCollide)
		{
			_collisionCD -= deltaTime;
			if (_collisionCD <= 0)
			{
				_canCollide == true;
				_collisionCD = INIT_COLLISION_CD;
			}
		}
	}


	void onCollision()
	{
		_canCollide = false;
	}

	//getters
	float getRadius() const
	{
		return _radius;
	}

	Vec2<float> getVel() const
	{
		return _vel;	
	}

	bool canCollide() const
	{
		return _canCollide;
	}

	//setters
	void setVel(const Vec2<float>& vel_in)
	{
		_vel = vel_in;
	}

private:

	float _radius;
	Vec2<float> _vel;
	float _collisionCD = INIT_COLLISION_CD;
	bool _canCollide = true;
};
