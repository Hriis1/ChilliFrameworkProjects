#pragma once

#include <algorithm>

#include "Entity.h"
#include "Colors.h"
#include "Drawable.h"

class Plank : public Entity
{
public:
	Plank(Vec2<float> anchor, float freeX, float minFreeY, float maxFreeY, float fatness = 8.0f, Color c = Colors::Yellow)
		:
		Entity({}, anchor, c),
		_minFreeYModel(minFreeY - anchor._y),
		_maxFreeYModel(maxFreeY - anchor._y),
		_freePtModel(freeX - anchor._x, _minFreeYModel),
		_fatness(fatness)
		, testModel(getModel())
	{}
	// generate the model dynamically on demand before returning the Drawable
	Drawable getDrawable()
	{
		std::vector<Vec2<float>> model;
		model.reserve(4);
		model.emplace_back(0.0f, 0.0f);
		model.push_back(_freePtModel);
		model.push_back(_freePtModel + Vec2<float>{ 0.0f,_fatness });
		model.emplace_back(0.0f, _fatness);
		setModel(std::move(model));
		return Entity::getDrawable();
	}
	void MoveFreeY(float deltaY)
	{
		setFreeY(getFreePt()._y + deltaY);
	}

	//getters
	Vec2<float> getFreePt() const
	{
		return _freePtModel + getPos();
	}

	Vec2<float> getPlankSurfaceVector() const
	{
		return -_freePtModel;
	}
	auto getPoints() const
	{
		const Vec2 pos = getPos();
		return std::make_pair(pos, pos + _freePtModel);
	}

	//setters
	void setFreeY(float freeY_in)
	{
		_freePtModel._y = std::clamp(freeY_in - getPos()._y, _minFreeYModel, _maxFreeYModel);
	}
	
	

private:
	float _minFreeYModel;
	float _maxFreeYModel;
	Vec2<float> _freePtModel;
	float _fatness;
	const std::vector<Vec2<float>>& testModel;
};

