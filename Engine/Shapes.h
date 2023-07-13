#pragma once
#include <vector>
#include "Vec2.h"

class ShapeMaker
{
public:
	static std::vector<Vec2<float>> makeStar(float outerRadius, float innerRadius, int nFlares = 5)
	{
		std::vector<Vec2<float>> star;
		star.reserve((size_t)nFlares * 2);
		const float dTheta = 2.0f * 3.14159f / float(nFlares * 2);
		for (int i = 0; i < nFlares * 2; i++)
		{
			const float rad = (i % 2 == 0) ? outerRadius : innerRadius;
			star.emplace_back(
				rad * cos(float(i) * dTheta),
				rad * sin(float(i) * dTheta)
			);
		}
		return star;
	}

	static std::vector<Vec2<float>> makeRectangle(float width, float height)
	{
		std::vector<Vec2<float>> rect;
		rect.emplace_back(0.0f, 0.0f);
		rect.emplace_back(width, 0.0f);
		rect.emplace_back(width, height);
		rect.emplace_back(0.0f, height);
		
		return rect;
	}
};