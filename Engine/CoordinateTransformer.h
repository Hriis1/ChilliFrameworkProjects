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
		const Vec2 offset = { float(Graphics::ScreenWidth / 2),float(Graphics::ScreenHeight / 2) };
		drawable.scaleIndependent(1.0f, -1.0f);
		drawable.translate(offset);
		drawable.Render(_gfx);
	}
private:
	Graphics& _gfx;
};
