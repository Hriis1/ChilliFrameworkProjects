#pragma once
#include <vector>
#include "Vec2.h"
#include "Graphics.h"

class CoordinateTransformer
{
public:
	CoordinateTransformer(Graphics& gfx)
		:
		gfx(gfx)
	{}
	void drawPolyLine(std::vector<Vec2<int>> poly, Color c)
	{
		Vec2<int> offset(gfx.ScreenWidth / 2, gfx.ScreenHeight / 2);
		for (auto& vert : poly)
		{
			vert += offset;
		}
		gfx.drawPolyLine(poly, c);
	}
private:
	Graphics& gfx;
};
