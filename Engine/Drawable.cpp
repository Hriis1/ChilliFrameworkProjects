#include "Drawable.h"

Drawable::Drawable(std::vector<Vec2<float>> model, Color c)
	: _model(std::move(model)), _color(c)
{
}

void Drawable::translate(const Vec2<float>& translation_in)
{
	_translation += translation_in;
}

void Drawable::scale(float scale_in)
{
	_scaleX *= scale_in;
	_scaleY *= scale_in;
	_translation *= scale_in;
}

void Drawable::scaleIndependent(float scaleX_in, float scaleY_in)
{
	_scaleX *= scaleX_in;
	_scaleY *= scaleY_in;
	_translation._x *= scaleX_in;
	_translation._y *= scaleY_in;
}

void Drawable::scaleX(float scaleX_in)
{
	_scaleX *= scaleX_in;
	_translation._x *= scaleX_in;
}

void Drawable::scaleY(float scaleY_in)
{
	_scaleY *= scaleY_in;
	_translation._y *= scaleY_in;
}

void Drawable::Render(Graphics& gfx)
{
	for (auto& vert : _model)
	{
		vert._x *= _scaleX;
		vert._y *= _scaleY;
		vert += _translation;
	}

	gfx.drawPolyLine(_model, _color);
}
