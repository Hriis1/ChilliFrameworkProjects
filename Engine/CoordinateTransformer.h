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
		Vec2<float> offset((float)_gfx.ScreenWidth / 2.0f, (float)_gfx.ScreenHeight / 2.0f);
		drawable.scaleY(-1.0f);
		drawable.translate(offset);
		drawable.Render(_gfx);
	}
private:
	Graphics& _gfx;
};
