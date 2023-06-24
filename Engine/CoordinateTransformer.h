#pragma once
#include <vector>
#include "Vec2.h"
#include "Graphics.h"
#include "Drawable.h"

class CoordinateTransformer
{
public:
	CoordinateTransformer(Graphics& gfx)
		:
		_gfx(gfx)
	{}
	void draw(Drawable& drawable) const
	{
		const Vec2<float> offset = { float(Graphics::ScreenWidth / 2),float(Graphics::ScreenHeight / 2) };
		drawable.applyTransformation(
			Mat3<float>::ScaleIndependent(1.0f, -1.0f) *
			Mat3<float>::Translation(offset._x, offset._y)
		);
		drawable.Render(_gfx);
	}
private:
	Graphics& _gfx;
};
