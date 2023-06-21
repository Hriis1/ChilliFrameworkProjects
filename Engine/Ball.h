#pragma once
#include "Colors.h"
#include "Shapes.h"
#include "Entity.h"


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
