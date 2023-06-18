#pragma once
#include <algorithm>

#include "Entity.h"
#include "Colors.h"
#include "Drawable.h"

class PlankVer2 : public Entity
{
public:
	PlankVer2(Vec2<float> anchorPos, float changingPointXDist, float maxPositiveYChange, float maxNegativeYChange, float fatness = 8.0f, Color c = Colors::Yellow)
		: Entity({}, _anchorPos , c),
		_anchorPos(anchorPos), _changingPointXDistance(changingPointXDist),_freePointPos(anchorPos._x + changingPointXDist, anchorPos._y), 
		_maxPositiveYChange(maxPositiveYChange), _maxNegativeYChange(maxNegativeYChange), _fatness(fatness)
	{

	}
	Drawable getDrawable()
	{
		std::vector<Vec2<float>> model;
		model.reserve(4);
		model.push_back(_anchorPos);
		model.emplace_back(_anchorPos._x, _anchorPos._y + _fatness);
		model.emplace_back(_freePointPos._x, _freePointPos._y + _fatness);
		model.push_back(_freePointPos);
		
		setModel(std::move(model));
		return Entity::getDrawable();
	}

	void moveFreePoint(float deltaY)
	{
		_freePointPos._y = std::clamp(_freePointPos._y + deltaY, _anchorPos._y + _maxNegativeYChange, _anchorPos._y + _maxPositiveYChange);
		
	}
private:
	Vec2<float> _anchorPos;
	float _changingPointXDistance;
	Vec2<float> _freePointPos;
	float _maxPositiveYChange;
	float _maxNegativeYChange;
	float _fatness;
};
