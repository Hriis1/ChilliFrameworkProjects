#include "Drawable.h"

Drawable::Drawable(const std::vector<Vec2<float>>& model, Color c)
	: _model(&model), _color(c)
{
}

void Drawable::applyTransformation(const Mat3<float>& transformation_in)
{
	_transformation = transformation_in * _transformation;
}

void Drawable::Render(Graphics& gfx)
{
	gfx.drawPolyLine(*_model, _transformation, _color);
}
