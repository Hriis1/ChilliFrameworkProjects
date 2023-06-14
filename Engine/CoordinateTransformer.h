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
			//Translate the shape so it behaves like its in a mathematical coordinate system
			vert._y *= -1;
			vert += offset;
		}
		gfx.drawPolyLine(poly, c);
	}
private:
	Graphics& gfx;
};
