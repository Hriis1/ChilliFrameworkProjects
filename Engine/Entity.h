#pragma once

#include <vector>
#include "Vec2.h"

class Entity
{
public:
	Entity(const std::vector<Vec2<float>>& model)
		: _model(model)
	{

	}
	Entity(const std::vector<Vec2<float>>& model, const Vec2<float>& pos)
		: _model(model), _pos(pos)
	{

	}

	void translateBy(const Vec2<float> offset)
	{
		_pos += offset;
	}

	//getters
	const Vec2<float>& getPos() const
	{
		return _pos;
	}

	float getScale() const
	{
		return _scale;
	}

	std::vector<Vec2<float>> getPolyLine() const
	{
		auto poly = _model;
		for (auto& vert : poly)
		{
			vert *= _scale;
			vert += _pos;
		}

		return poly;
	}

	//setters
	void setPos(const Vec2<float>& newPos)
	{
		_pos = newPos;
	}

	void setScale(float scale)
	{
		_scale = scale;
	}
private:
	std::vector<Vec2<float>> _model;
	Vec2<float> _pos = { 0.0f, 0.0f };
	float _scale = 1.0f;
};

