#pragma once

#include <vector>
#include "Graphics.h"
#include "Vec2.h"
#include "Mat3.h"

class Drawable
{
public:
	Drawable(const std::vector<Vec2<float>>& model, Color c);

	void applyTransformation(const Mat3<float>& transformation_in);

	void Render(Graphics& gfx);
private:
	const std::vector<Vec2<float>>* _model;
	Color _color;
	Mat3<float> _transformation = Mat3<float>::Identity();
};

