#pragma once

#include <vector>
#include "Graphics.h"
#include "Vec2.h"

class Drawable
{
public:
	Drawable(const std::vector<Vec2<float>>& model, Color c);

	void translate(const Vec2<float>& translation_in);
	void scale(float scale_in);
	void scaleIndependent(float scaleX_in, float scaleY_in);
	void scaleX(float scaleX_in);
	void scaleY(float scaleY_in);
	void Rotate(float angle);

	void Render(Graphics& gfx);
private:
	const std::vector<Vec2<float>>* _model;
	Vec2<float> _translation = {0.0f, 0.0f};
	float _scaleX = 1.0f;
	float _scaleY = 1.0f;
	float _angle = 0.0f;
	Color _color;
};

