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
	void drawPolyLine(std::vector<Vec2<float>> poly, Color c)
	{
		Vec2<float> offset((float)gfx.ScreenWidth / 2.0f, (float)gfx.ScreenHeight / 2.0f);
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
