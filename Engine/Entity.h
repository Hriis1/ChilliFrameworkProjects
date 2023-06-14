#pragma once

#include <vector>
#include "Vec2.h"

class Entity
{
public:
	Entity(const std::vector<Vec2<int>>& model)
		: _model(model)
	{

	}

	void translateBy(const Vec2<int> offset)
	{
		_pos += offset;
	}

	//getters
	const Vec2<int>& getPos() const
	{
		return _pos;
	}

	std::vector<Vec2<int>> getPolyLine() const
	{
		auto poly = _model;
		for (auto& vert : poly)
		{
			vert += _pos;
		}

		return poly;
	}

	//setters
	void setPos(const Vec2<int>& newPos)
	{
		_pos = newPos;
	}
private:
	Vec2<int> _pos = { 0.0f, 0.0f };
	std::vector<Vec2<int>> _model;
};

