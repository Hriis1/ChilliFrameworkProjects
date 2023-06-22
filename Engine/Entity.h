#pragma once

#include <vector>
#include "Vec2.h"
#include "Drawable.h"

class Entity
{
public:
	Entity(const std::vector<Vec2<float>>& model, Color c = Colors::White)
		: _model(model), _color(c)
	{

	}
	Entity(const std::vector<Vec2<float>>& model, const Vec2<float>& pos, Color c = Colors::White)
		: _model(model), _pos(pos), _color(c)
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
	
	float getAngle()
	{
		return _angle;
	}

	Drawable getDrawable() const
	{
		 Drawable drawable(_model, _color);
		 drawable.scale(_scale);
		 drawable.translate(_pos);
		 return drawable;
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

	void setColor(Color c)
	{
		_color = c;
	}

	void setAngle(float a)
	{
		_angle = a;
	}


protected:
	void setModel(std::vector<Vec2<float>> model_in)
	{
		_model = std::move(model_in);
	}

	const std::vector<Vec2<float>>& getModel()
	{
		return _model;
	}
private:
	std::vector<Vec2<float>> _model;
	Vec2<float> _pos = { 0.0f, 0.0f };
	float _angle = 0.0f;
	float _scale = 1.0f;
	Color _color;
};

